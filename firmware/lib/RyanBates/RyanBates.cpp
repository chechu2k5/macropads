
#include "RyanBates.h"

#include "KeyPad.h"
#include "EasyButton.h"
#include "Encoder.h"

using namespace MacroPad;

#if defined(RYANBATES_6KEY_2ROTARY_BOARD)
#include "6K2R_V1.h"
#elif defined(RYANBATES_13KEY_2ROTARY_BOARD)
#include "13K2R_V04.h"
#else
#error "No or invalid board selected!"
#endif

namespace RyanBates
{
    struct ButtonState
    {
        bool pressed = false;
        bool released = false;
        bool longPress = false;
    };

    ButtonState buttonStates[NUM_BUTTONS];

    ModeActions modeActions = ModeActions::None;

    char keys[] = "ABCDEFGHIJKLMNOP";

    Keypad keypad = Keypad(keys, rowPins, colPins, ROWS, COLS);

    Report const encoderReports[NUM_ENCODERS][2] = {{
                                                        {Modifiers::LALT, Scancodes::KEY_TAB},
                                                        {static_cast<Modifiers>(Modifiers::LALT | Modifiers::LSHIFT), Scancodes::KEY_TAB},
                                                    },
                                                    {
                                                        {MediaKeys::VOL_DOWN},
                                                        {MediaKeys::VOL_UP},
                                                    }};
    int32_t encoderPos[NUM_ENCODERS] = {-999, -999};

    EasyButton modeButton = EasyButton(A0);

    uint8_t currentMode = 0, prevMode = 1;

    void updateMode()
    {
        modeButton.read();

        if (modeButton.isReleased())
        {
            bool changed = true;
            switch (modeActions)
            {
            case ModeActions::Next:
            {
                prevMode = currentMode;
                currentMode = (currentMode + 1) % 4;
            }
            break;
            case ModeActions::Reset:
            {
                prevMode = currentMode;
                currentMode = 0;
            }
            break;
            case ModeActions::QuickFlip:
            {
                auto tmp = currentMode;
                currentMode = prevMode;
                prevMode = tmp;
            }
            break;

            case ModeActions::None:
            default:
            {
                changed = false;
            }
            break;
            }

            modeActions = ModeActions::None;

            if (changed)
            {
                Report const *press;
                Report const *longPress;

                switch (currentMode)
                {
                case 1:
                {
                    press = Mode1::pressReports;
                    longPress = Mode1::longPressReports;
                }
                break;

                case 2:
                {
                    press = Mode2::pressReports;
                    longPress = Mode2::longPressReports;
                }
                break;

                case 3:
                {
                    press = Mode3::pressReports;
                    longPress = Mode3::longPressReports;
                }
                break;

                default:
                case 0:
                {
                    press = Mode0::pressReports;
                    longPress = Mode0::longPressReports;
                }
                break;
                }

                memcpy(pressReports, press, sizeof(pressReports));
                memcpy(longPressReports, longPress, sizeof(longPressReports));
            }
        }

        uint8_t const b0 = currentMode & 1;
        uint8_t const b1 = (currentMode >> 1) & 1;

        digitalWrite(LED_MODE0, b0);
        digitalWrite(LED_MODE1, b1);
    }

    void updateEncoder(MacroPad::MacroPad const &macroPad, Encoder &encoder, int32_t &currentPosition, Report const *const encoderReports)
    {
        int32_t const newPos = encoder.read() / 4;

        if (newPos == currentPosition)
            return;

        macroPad.send(encoderReports[(newPos > currentPosition) ? 0 : 1]);
        macroPad.releaseAll();
        currentPosition = newPos;
    }

    void update(MacroPad::MacroPad const &macroPad)
    {
        for (int i = 0; i < NUM_ENCODERS; i++)
        {
            updateEncoder(macroPad, encoders[i], encoderPos[i], encoderReports[i]);
        }

        updateMode();

        if (keypad.getKeys())
        {
            for (int i = 0; i < NUM_BUTTONS; i++)
            {
                auto &buttonState = buttonStates[i];

                if (buttonState.released)
                {
                    if (buttonState.longPress)
                    {
                        macroPad.send(longPressReports[i]);
                        macroPad.releaseAll();
                    }
                    else if (buttonState.pressed)
                    {
                        macroPad.send(pressReports[i]);
                        macroPad.releaseAll();
                    }

                    buttonState.released = buttonState.pressed = buttonState.longPress = false;
                }
            }
        }
    }

    void init()
    {
        pinMode(LED_MODE0, OUTPUT);
        digitalWrite(LED_MODE0, LOW);

        pinMode(LED_MODE1, OUTPUT);
        digitalWrite(LED_MODE1, LOW);

        pinMode(LED_BUILTIN_TX, INPUT);

        memcpy(pressReports, Mode0::pressReports, sizeof(pressReports));
        memcpy(longPressReports, Mode0::longPressReports, sizeof(longPressReports));

        modeButton.begin();
        modeButton.onPressed([]() {
            modeActions = ModeActions::Next;
        });
        modeButton.onPressedFor(350, []() {
            modeActions = ModeActions::Reset;
        });
        modeButton.onSequence(2, 500, []() {
            modeActions = ModeActions::QuickFlip;
        });

        keypad.setHoldTime(350);

        keypad.addEventListener([](char const key) {
            auto const index = key - 'A';

            auto &buttonState = buttonStates[index];

            switch (keypad.getState())
            {
            case PRESSED:
            {
                buttonState.pressed = true;
            }
            break;

            case RELEASED:
            {
                buttonState.released = true;
            }
            break;

            case HOLD:
            {
                buttonState.longPress = true;
            }
            break;

            default:
                break;
            }
        });
    }

} // namespace RyanBates
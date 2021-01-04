
#include "RyanBates.h"

#include "KeyPad.h"
#include "EasyButton.h"
#include "Encoder.h"

using namespace MacroPad;

namespace RyanBates
{

#if defined(RYANBATES_6KEY_2ROTARY_BOARD)

    Report const longPressReports[] = {
        {},                                   // LHS encoder button
        {},                                   // Top row button 1
        {},                                   // Top row button 2
        {},                                   // RHS encoder button
        {},                                   // Bottom row button 1
        {},                                   // Bottom row button 2
        {},                                   // Bottom row button 3
        {Modifiers::LMETA, Scancodes::KEY_L}, // Bottom row button 4
    };

    Report const keyReports[] = {
        {MediaKeys::MUTE},                     // LHS encoder button
        {Modifiers::NONE, Scancodes::KEY_F22}, // Top row button 1
        {Modifiers::NONE, Scancodes::KEY_F23}, // Top row button 2
        {MediaKeys::PLAYPAUSE},                // RHS encoder button
        {Modifiers::NONE, Scancodes::KEY_F13}, // Bottom row button 1
        {Modifiers::NONE, Scancodes::KEY_F14}, // Bottom row button 2
        {Modifiers::NONE, Scancodes::KEY_F15}, // Bottom row button 3
        {Modifiers::NONE, Scancodes::KEY_F16}, // Bottom row button 4
    };

    uint8_t rowPins[ROWS] = {4, 5};
    uint8_t colPins[COLS] = {6, 7, 8, 9};

    Encoder encoders[] = {
        {10, 16}, // the LEFT encoder (encoder A)
        {14, 15}  // the RIGHT encoder (encoder B)
    };

#elif defined(RYANBATES_13KEY_2ROTARY_BOARD)

    Report const longPressReports[] = {
        {},                                   // Row 4 Button 1
        {},                                   // Row 4 Button 2
        {},                                   // Row 4 Button 3
        {},                                   // Row 4 Button 4
        {Modifiers::LMETA, Scancodes::KEY_L}, // Row 4 Button 5

        {}, // Row 3 Button 1
        {}, // Row 3 Button 2
        {}, // Row 3 Button 3
        {}, // Row 3 Button 4

        {}, // LHS Rotary Button
        {}, // Row 2 Button 2
        {}, // Row 2 Button 3
        {}, // RHS Rotary Buttons

        {}, // Row 1 Button 1 => KEY14
        {}, // Row 1 Button 1 => KEY15
        {}, // Row 1 Button 1 => KEY16
    };

    Report const keyReports[] = {
        {Modifiers::NONE, Scancodes::KEY_F13}, // Row 4 Button 1
        {Modifiers::NONE, Scancodes::KEY_F14}, // Row 4 Button 2
        {Modifiers::NONE, Scancodes::KEY_F15}, // Row 4 Button 3
        {Modifiers::NONE, Scancodes::KEY_F16}, // Row 4 Button 4
        {},                                    // Row 4 Button 5

        {}, // Row 3 Button 1
        {}, // Row 3 Button 2
        {}, // Row 3 Button 3
        {}, // Row 3 Button 4

        {MediaKeys::SCAN_PREV}, // LHS Rotary Button
        {MediaKeys::MUTE},      // Row 2 Button 2
        {MediaKeys::PLAYPAUSE}, // Row 2 Button 3
        {MediaKeys::SCAN_NEXT}, // RHS Rotary Buttons

        {}, // Row 1 Button 1 => KEY14
        {}, // Row 1 Button 1 => KEY15
        {}, // Row 1 Button 1 => KEY16
    };

    uint8_t rowPins[ROWS] = {2, 3, 4, 5};
    uint8_t colPins[COLS] = {6, 7, 8, 9};

    Encoder encoders[] = {
        {14, 15}, // the LEFT encoder (encoder A)
        {10, 16}  // the RIGHT encoder (encoder B)
    };

#else

#error "No or invalid board selected!"

#endif

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
            switch (modeActions)
            {
            case ModeActions::None:
            {
            }
            break;
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

            default:
                break;
            }

            modeActions = ModeActions::None;
        }

        uint8_t const b0 = currentMode & 1;
        uint8_t const b1 = (currentMode >> 1) & 1;

        digitalWrite(Mode1, b0);
        digitalWrite(Mode2, b1);
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
                        macroPad.send(keyReports[i]);
                        macroPad.releaseAll();
                    }

                    buttonState.released = buttonState.pressed = buttonState.longPress = false;
                }
            }
        }
    }

    void init()
    {
        pinMode(Mode1, OUTPUT);
        digitalWrite(Mode1, LOW);

        pinMode(Mode2, OUTPUT);
        digitalWrite(Mode2, LOW);

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
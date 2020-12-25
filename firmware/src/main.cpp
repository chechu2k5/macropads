#include <Arduino.h>
#include <macroPad.h>
#include <Encoder.h>
#include <Keypad.h>

using Scancodes = MacroPad::Scancodes;
using Modifiers = MacroPad::Modifiers;
using Report = MacroPad::MacroPad::Report;
using ReportType = MacroPad::MacroPad::ReportType;
using MediaKeys = MacroPad::MediaKeys;

// ------------------------------------------------------------------
// BOARD SPECIFIC STUFF HERE
// ------------------------------------------------------------------

#if defined(RYANBATES_6KEY_2ROTARY_BOARD)

Encoder encoderA(10, 16); // the LEFT encoder (encoder A)
int32_t encoderAPos = -999;

Encoder encoderB(14, 15); // the RIGHT encoder (encoder B)
int32_t encoderBPos = -999;

uint8_t const ROWS = 2;
uint8_t const COLS = 4;

uint8_t rowPins[ROWS] = {4, 5};
uint8_t colPins[COLS] = {6, 7, 8, 9};

#elif RYANBATES_13KEY_2ROTARY_BOARD

Encoder encoderA(14, 15); //the LEFT encoder (encoder A)
int32_t encoderAPos = -999;

Encoder encoderB(10, 16); //the RIGHT encoder (encoder B)
int32_t encoderBPos = -999;

// ------------------------------------------------------------------
uint8_t const ROWS = 4;
uint8_t const COLS = 4;

uint8_t rowPins[ROWS] = {2, 3, 4, 5};
uint8_t colPins[COLS] = {6, 7, 8, 9};

#endif

// ------------------------------------------------------------------

char keys[] = "ABCDEFGHIJKLMNOP";

Keypad keypad = Keypad(keys, rowPins, colPins, ROWS, COLS);

// ------------------------------------------------------------------

MacroPad::MacroPad const macroPad;

// ------------------------------------------------------------------

#if defined(RYANBATES_6KEY_2ROTARY_BOARD)

//     A  M
//   R B B R
//   B B B B
// L
// L

// A: Analog Potentiometer
// M: Mode button
// R: Rotary Encoder (or) Button
// B: Button
// L: LED

Report const keyReports[] = {
    {ReportType::Keyboard, Modifiers::LALT, {Scancodes::KEY_F4}, MediaKeys::KEY_NONE},     // LHS encoder button  => LALT+F4
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F22}, MediaKeys::KEY_NONE},    // Top row button 1    => F22
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F23}, MediaKeys::KEY_NONE},    // Top row button 2    => F23
    {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_PLAYPAUSE}, // RHS encoder button  => KEY_PLAYPAUSE
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F13}, MediaKeys::KEY_NONE},    // Bottom row button 1 => F13
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F14}, MediaKeys::KEY_NONE},    // Bottom row button 2 => F14
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F15}, MediaKeys::KEY_NONE},    // Bottom row button 3 => F15
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F16}, MediaKeys::KEY_NONE},    // Bottom row button 4 => F16
    // {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_SCAN_PREV}, // Bottom row button 1 => prev song
    // {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_STOP},      // Bottom row button 1 => stop playing
    // {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_MUTE},      // Bottom row button 1 => mute
    // {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_SCAN_NEXT}, // Bottom row button 1 => next song
};

Report const encoderAReports[] = {
    {ReportType::Keyboard, static_cast<Modifiers>(Modifiers::LALT), {Scancodes::KEY_TAB}, MediaKeys::KEY_NONE},
    {ReportType::Keyboard, static_cast<Modifiers>(Modifiers::LALT | Modifiers::LSHIFT), {Scancodes::KEY_TAB}, MediaKeys::KEY_NONE},
};

Report const encoderBReports[] = {
    {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_VOL_DOWN},
    {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_VOL_UP},
};

#elif defined(RYANBATES_13KEY_2ROTARY_BOARD)
// ----- LAYOUT ----
//     A  M
//   R B B R
//   B B B B
//   B B B B
// L
// L
// ----- ----- ----

// A: Analog Potentiometer
// M: Mode button
// R: Rotary Encoder (or) Button
// B: Button
// L: LED

Report const keyReports[] = {
    {ReportType::Keyboard, Modifiers::LALT, {Scancodes::KEY_F4}, MediaKeys::KEY_NONE},     // LHS encoder button  => LALT+F4
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F22}, MediaKeys::KEY_NONE},    // Top row button 1    => F22
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F23}, MediaKeys::KEY_NONE},    // Top row button 2    => F23
    {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_PLAYPAUSE}, // RHS encoder button  => KEY_PLAYPAUSE
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F13}, MediaKeys::KEY_NONE},    // Middle row button 1 => F13
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F14}, MediaKeys::KEY_NONE},    // Middle row button 2 => F14
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F15}, MediaKeys::KEY_NONE},    // Middle row button 3 => F15
    {ReportType::Keyboard, Modifiers::NONE, {Scancodes::KEY_F16}, MediaKeys::KEY_NONE},    // Middle row button 4 => F16
    {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_SCAN_PREV}, // Bottom row button 1 => prev song
    {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_STOP},      // Bottom row button 1 => stop playing
    {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_MUTE},      // Bottom row button 1 => mute
    {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_SCAN_NEXT}, // Bottom row button 1 => next song
};

Report const encoderAReports[] = {
    {ReportType::Keyboard, static_cast<Modifiers>(Modifiers::LALT), {Scancodes::KEY_TAB}, MediaKeys::KEY_NONE},
    {ReportType::Keyboard, static_cast<Modifiers>(Modifiers::LALT | Modifiers::LSHIFT), {Scancodes::KEY_TAB}, MediaKeys::KEY_NONE},
};

Report const encoderBReports[] = {
    {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_VOL_DOWN},
    {ReportType::Media, Modifiers::NONE, {Scancodes::KEY_NONE}, MediaKeys::KEY_VOL_UP},
};

#else

#error UNKNOWN BOARD TYPE: Select the board via platformio.ini > build_flags

#endif

void updateEncoder(Encoder &encoder, int32_t &currentPosition, Report const *const encoderReports)
{
  int32_t const newPos = encoder.read() / 4;

  if (newPos == currentPosition)
    return;

  macroPad.send(encoderReports[(newPos > currentPosition) ? 0 : 1]);
  macroPad.releaseAll();
  currentPosition = newPos;
}

void setup()
{
  Serial.begin(9600);
  macroPad.begin();
}

void loop()
{
  auto const key = keypad.getKey();

  if (key)
  {
    auto const index = key - 'A';

    macroPad.send(keyReports[index]);
    macroPad.releaseAll();
  }

  updateEncoder(encoderA, encoderAPos, encoderAReports);
  updateEncoder(encoderB, encoderBPos, encoderBReports);

  delay(1);
}

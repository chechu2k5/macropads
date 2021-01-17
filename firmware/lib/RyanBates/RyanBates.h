#pragma once

#include <Arduino.h>

#include "MacroPad.h"

#if defined(RYANBATES_6KEY_2ROTARY_BOARD)

// ----- LAYOUT ----
//   K K A M
//   R B B R
//   B B B B
// L
// L
// ----- LAYOUT ----

// A: Analog Potentiometer
// M: Mode button
// R: Rotary Encoder (or) Button
// B: Button
// L: LED

uint8_t const ROWS = 2;
uint8_t const COLS = 4;

#elif defined(RYANBATES_13KEY_2ROTARY_BOARD)

// ----- LAYOUT ----
//   K K A M
//   R B B R
//   B B B B
//   B B B B
// L
// L
// ----- LAYOUT ----

// A: Analog Potentiometer
// M: Mode button
// R: Rotary Encoder (or) Button
// B: Button
// K: Key (Button)
// L: LED

uint8_t const ROWS = 4;
uint8_t const COLS = 4;

#else

#error "No or invalid board selected!"

#endif

using namespace MacroPad;

namespace RyanBates
{
    enum ModeActions
    {
        None,
        Next,
        Reset,
        QuickFlip
    };

    uint8_t const LED_MODE0 = A2;
    uint8_t const LED_MODE1 = A3;
    uint8_t const NUM_BUTTONS = ROWS * COLS;
    uint8_t const NUM_ENCODERS = 2;

    void init();
    void update(MacroPad::MacroPad const &);

} // namespace RyanBates

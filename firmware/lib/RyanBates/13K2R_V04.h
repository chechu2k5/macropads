#pragma once

#include "KeyPad.h"
#include "EasyButton.h"
#include "Encoder.h"

namespace RyanBates
{
    // this is somewhat wasteful of RAM but I wasnt able to get it working when moved into PROGMEM
    // as this is not pure data but invokes overloaded constructors
    namespace Mode0
    {
        Report const pressReports[] =
            {
                {Modifiers::NONE, Scancodes::KEY_F13}, // Row 4 Button 1
                {Modifiers::NONE, Scancodes::KEY_F14}, // Row 4 Button 2
                {Modifiers::NONE, Scancodes::KEY_F15}, // Row 4 Button 3
                {Modifiers::NONE, Scancodes::KEY_F16}, // Row 4 Button 4
                {},                                    // Row 4 Button 5

                {},                                    // Row 3 Button 1
                {},                                    // Row 3 Button 2
                {},                                    // Row 3 Button 3
                {Modifiers::NONE, Scancodes::KEY_F23}, // Row 3 Button 4

                {MediaKeys::SCAN_PREV}, // LHS Rotary Encoder's Button
                {MediaKeys::MUTE},      // Row 2 Button 2
                {MediaKeys::PLAYPAUSE}, // Row 2 Button 3
                {MediaKeys::SCAN_NEXT}, // RHS Rotary Encoder's Button

                {},                                   // Row 1 Button 1 => KEY14
                {Modifiers::LMETA, Scancodes::KEY_L}, // Row 1 Button 1 => KEY15
                {},                                   // Row 1 Button 1 => KEY16
        };

        Report const longPressReports[] =
            {
                {}, // Row 4 Button 1
                {}, // Row 4 Button 2
                {}, // Row 4 Button 3
                {}, // Row 4 Button 4
                {}, // Row 4 Button 5

                {}, // Row 3 Button 1
                {}, // Row 3 Button 2
                {}, // Row 3 Button 3
                {}, // Row 3 Button 4

                {}, // LHS Rotary Encoder's Button
                {}, // Row 2 Button 2
                {}, // Row 2 Button 3
                {}, // RHS Rotary Encoder's Button

                {}, // Row 1 Button 1 => KEY14
                {}, // Row 1 Button 1 => KEY15
                {}, // Row 1 Button 1 => KEY16
        };

    } // namespace Mode0

    namespace Mode1
    {
        Report const pressReports[] =
            {
                {}, // Row 4 Button 1
                {}, // Row 4 Button 2
                {}, // Row 4 Button 3
                {}, // Row 4 Button 4
                {}, // Row 4 Button 5

                {}, // Row 3 Button 1
                {}, // Row 3 Button 2
                {}, // Row 3 Button 3
                {}, // Row 3 Button 4

                {}, // LHS Rotary Encoder's Button
                {}, // Row 2 Button 2
                {}, // Row 2 Button 3
                {}, // RHS Rotary Encoder's Button

                {}, // Row 1 Button 1 => KEY14
                {}, // Row 1 Button 1 => KEY15
                {}, // Row 1 Button 1 => KEY16
        };

        Report const longPressReports[] =
            {
                {}, // Row 4 Button 1
                {}, // Row 4 Button 2
                {}, // Row 4 Button 3
                {}, // Row 4 Button 4
                {}, // Row 4 Button 5

                {}, // Row 3 Button 1
                {}, // Row 3 Button 2
                {}, // Row 3 Button 3
                {}, // Row 3 Button 4

                {}, // LHS Rotary Encoder's Button
                {}, // Row 2 Button 2
                {}, // Row 2 Button 3
                {}, // RHS Rotary Encoder's Button

                {}, // Row 1 Button 1 => KEY14
                {}, // Row 1 Button 1 => KEY15
                {}, // Row 1 Button 1 => KEY16
        };

    } // namespace Mode1

    namespace Mode2
    {
        Report const pressReports[] =
            {
                {}, // Row 4 Button 1
                {}, // Row 4 Button 2
                {}, // Row 4 Button 3
                {}, // Row 4 Button 4
                {}, // Row 4 Button 5

                {}, // Row 3 Button 1
                {}, // Row 3 Button 2
                {}, // Row 3 Button 3
                {}, // Row 3 Button 4

                {}, // LHS Rotary Encoder's Button
                {}, // Row 2 Button 2
                {}, // Row 2 Button 3
                {}, // RHS Rotary Encoder's Button

                {}, // Row 1 Button 1 => KEY14
                {}, // Row 1 Button 1 => KEY15
                {}, // Row 1 Button 1 => KEY16
        };

        Report const longPressReports[] =
            {
                {}, // Row 4 Button 1
                {}, // Row 4 Button 2
                {}, // Row 4 Button 3
                {}, // Row 4 Button 4
                {}, // Row 4 Button 5

                {}, // Row 3 Button 1
                {}, // Row 3 Button 2
                {}, // Row 3 Button 3
                {}, // Row 3 Button 4

                {}, // LHS Rotary Encoder's Button
                {}, // Row 2 Button 2
                {}, // Row 2 Button 3
                {}, // RHS Rotary Encoder's Button

                {}, // Row 1 Button 1 => KEY14
                {}, // Row 1 Button 1 => KEY15
                {}, // Row 1 Button 1 => KEY16
        };

    } // namespace Mode2

    namespace Mode3
    {
        Report const pressReports[] =
            {
                {}, // Row 4 Button 1
                {}, // Row 4 Button 2
                {}, // Row 4 Button 3
                {}, // Row 4 Button 4
                {}, // Row 4 Button 5

                {}, // Row 3 Button 1
                {}, // Row 3 Button 2
                {}, // Row 3 Button 3
                {}, // Row 3 Button 4

                {}, // LHS Rotary Encoder's Button
                {}, // Row 2 Button 2
                {}, // Row 2 Button 3
                {}, // RHS Rotary Encoder's Button

                {}, // Row 1 Button 1 => KEY14
                {}, // Row 1 Button 1 => KEY15
                {}, // Row 1 Button 1 => KEY16
        };

        Report const longPressReports[] =
            {
                {}, // Row 4 Button 1
                {}, // Row 4 Button 2
                {}, // Row 4 Button 3
                {}, // Row 4 Button 4
                {}, // Row 4 Button 5

                {}, // Row 3 Button 1
                {}, // Row 3 Button 2
                {}, // Row 3 Button 3
                {}, // Row 3 Button 4

                {}, // LHS Rotary Encoder's Button
                {}, // Row 2 Button 2
                {}, // Row 2 Button 3
                {}, // RHS Rotary Encoder's Button

                {}, // Row 1 Button 1 => KEY14
                {}, // Row 1 Button 1 => KEY15
                {}, // Row 1 Button 1 => KEY16
        };

    } // namespace Mode3

    Report longPressReports[NUM_BUTTONS];

    Report pressReports[NUM_BUTTONS];

    uint8_t rowPins[ROWS] = {2, 3, 4, 5};
    uint8_t colPins[COLS] = {6, 7, 8, 9};

    Encoder encoders[] = {
        {14, 15}, // the LEFT encoder (encoder A)
        {10, 16}  // the RIGHT encoder (encoder B)
    };

} // namespace RyanBates
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
        Report const pressReports[] = {
            {MediaKeys::MUTE},                     // LHS Rotary Encoder's button
            {Modifiers::NONE, Scancodes::KEY_F22}, // Top row button 1
            {Modifiers::NONE, Scancodes::KEY_F23}, // Top row button 2
            {MediaKeys::PLAYPAUSE},                // RHS Rotary Encoder's button
            {Modifiers::NONE, Scancodes::KEY_F13}, // Bottom row button 1
            {Modifiers::NONE, Scancodes::KEY_F14}, // Bottom row button 2
            {Modifiers::NONE, Scancodes::KEY_F15}, // Bottom row button 3
            {Modifiers::NONE, Scancodes::KEY_F16}, // Bottom row button 4
        };

        Report const longPressReports[] = {
            {},                                   // LHS Rotary Encoder's button
            {},                                   // Top row button 1
            {},                                   // Top row button 2
            {},                                   // RHS Rotary Encoder's button
            {},                                   // Bottom row button 1
            {},                                   // Bottom row button 2
            {},                                   // Bottom row button 3
            {Modifiers::LMETA, Scancodes::KEY_L}, // Bottom row button 4
        };

    } // namespace Mode0

    namespace Mode1
    {
        Report const pressReports[] = {
            {}, // LHS Rotary Encoder's button
            {}, // Top row button 1
            {}, // Top row button 2
            {}, // RHS Rotary Encoder's button
            {}, // Bottom row button 1
            {}, // Bottom row button 2
            {}, // Bottom row button 3
            {}, // Bottom row button 4
        };

        Report const longPressReports[] = {
            {}, // LHS Rotary Encoder's button
            {}, // Top row button 1
            {}, // Top row button 2
            {}, // RHS Rotary Encoder's button
            {}, // Bottom row button 1
            {}, // Bottom row button 2
            {}, // Bottom row button 3
            {}, // Bottom row button 4
        };

    } // namespace Mode1

    namespace Mode2
    {
        Report const pressReports[] = {
            {MediaKeys::MUTE}, // LHS Rotary Encoder's button
            {},                // Top row button 1
            {},                // Top row button 2
            {},                // RHS Rotary Encoder's button
            {},                // Bottom row button 1
            {},                // Bottom row button 2
            {},                // Bottom row button 3
            {},                // Bottom row button 4
        };

        Report const longPressReports[] = {
            {}, // LHS Rotary Encoder's button
            {}, // Top row button 1
            {}, // Top row button 2
            {}, // RHS Rotary Encoder's button
            {}, // Bottom row button 1
            {}, // Bottom row button 2
            {}, // Bottom row button 3
            {}, // Bottom row button 4
        };

    } // namespace Mode2

    namespace Mode3
    {
        Report const pressReports[] = {
            {MediaKeys::MUTE}, // LHS Rotary Encoder's button
            {},                // Top row button 1
            {},                // Top row button 2
            {},                // RHS Rotary Encoder's button
            {},                // Bottom row button 1
            {},                // Bottom row button 2
            {},                // Bottom row button 3
            {},                // Bottom row button 4
        };

        Report const longPressReports[] = {
            {}, // LHS Rotary Encoder's button
            {}, // Top row button 1
            {}, // Top row button 2
            {}, // RHS Rotary Encoder's button
            {}, // Bottom row button 1
            {}, // Bottom row button 2
            {}, // Bottom row button 3
            {}, // Bottom row button 4
        };

    } // namespace Mode3

    Report longPressReports[NUM_BUTTONS];
    Report pressReports[NUM_BUTTONS];

    uint8_t rowPins[ROWS] = {4, 5};
    uint8_t colPins[COLS] = {6, 7, 8, 9};

    Encoder encoders[] = {
        {10, 16}, // the LEFT encoder (encoder A)
        {14, 15}  // the RIGHT encoder (encoder B)
    };

} // namespace RyanBates
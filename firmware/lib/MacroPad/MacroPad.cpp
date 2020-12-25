#include <Arduino.h>
#include "MacroPad.h"

namespace MacroPad
{
    static const uint8_t _hidReportDescriptor[] PROGMEM = {
        //  Keyboard
        0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
        0x09, 0x06,       // USAGE (Keyboard)
        0xa1, 0x01,       // COLLECTION (Application)
        0x85, 0x02,       //   REPORT_ID (2)
        0x05, 0x07,       //   USAGE_PAGE (Keyboard)
        0x19, 0xe0,       //   USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7,       //   USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00,       //   LOGICAL_MINIMUM (0)
        0x25, 0x01,       //   LOGICAL_MAXIMUM (1)
        0x75, 0x01,       //   REPORT_SIZE (1)
        0x95, 0x08,       //   REPORT_COUNT (8)
        0x81, 0x02,       //   INPUT (Data,Var,Abs)
        0x95, 0x01,       //   REPORT_COUNT (1)
        0x75, 0x08,       //   REPORT_SIZE (8)
        0x81, 0x03,       //   INPUT (Cnst,Var,Abs)
        0x95, 0x06,       //   REPORT_COUNT (6)
        0x75, 0x08,       //   REPORT_SIZE (8)
        0x15, 0x00,       //   LOGICAL_MINIMUM (0)
        0x26, 0xff, 0x00, //   LOGICAL_MAXIMUM (255)
        0x05, 0x07,       //   USAGE_PAGE (Keyboard)
        0x19, 0x00,       //   USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x73,       //   USAGE_MAXIMUM (Keyboard F24)
        0x81, 0x00,       //   INPUT (Data,Ary,Abs)
        0xc0,             // END_COLLECTION

        // remote control
        0x05, 0x0C, // Usage Page (Consumer)
        0x09, 0x01, // Usage (Consumer Control)
        0xA1, 0x01, // Collection (Application)
        0x85, 0x03, //   Report ID (3)
        0x05, 0x0C, //   Usage Page (Consumer)
        0x15, 0x00, //   Logical Minimum (0)
        0x25, 0x01, //   Logical Maximum (1)
        0x75, 0x01, //   Report Size (1)
        0x95, 0x08, //   Report Count (8)
        0x09, 0xB5, //   Usage (Scan Next Track)
        0x09, 0xB6, //   Usage (Scan Previous Track)
        0x09, 0xB7, //   Usage (Stop)
        0x09, 0xB8, //   Usage (Eject)
        0x09, 0xCD, //   Usage (Play/Pause)
        0x09, 0xE2, //   Usage (Mute)
        0x09, 0xE9, //   Usage (Volume Increment)
        0x09, 0xEA, //   Usage (Volume Decrement)
        0x81, 0x02, //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0xC0,       // End Collection
    };

    MacroPad::MacroPad(void)
    {
        static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
        HID().AppendDescriptor(&node);
    }

    void MacroPad::begin(void) const
    {
    }

    void MacroPad::end(void) const
    {
    }

    void MacroPad::send(Report const &report) const
    {
        if (report.reportType == ReportType::Keyboard)
        {
            uint8_t const keys[8] = {static_cast<uint8_t>(report.modifiers),
                                     0x00,
                                     static_cast<uint8_t>(report.scancodes[0]),
                                     static_cast<uint8_t>(report.scancodes[1]),
                                     static_cast<uint8_t>(report.scancodes[2]),
                                     static_cast<uint8_t>(report.scancodes[3]),
                                     static_cast<uint8_t>(report.scancodes[4]),
                                     static_cast<uint8_t>(report.scancodes[5])};
            HID().SendReport(2, keys, 8);
        }
        else
        {
            uint8_t key = static_cast<uint8_t>(report.mediaKey);
            HID().SendReport(3, &key, 1);
        }
    }

    void MacroPad::releaseAll() const
    {
        uint8_t const bytes[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        HID().SendReport(2, bytes, 8);
        HID().SendReport(3, bytes, 1);
    }

} // namespace MacroPad

#include <Arduino.h>

#include <HID.h>

#include "MacroPad.h"
namespace MacroPad
{
    static const uint8_t _hidReportDescriptor[] PROGMEM = {
        //  Keyboard
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x06, // USAGE (Keyboard)
        0xa1, 0x01, // COLLECTION (Application)
        0x85, 0x02, //   REPORT_ID (2)
        0x05, 0x07, //   USAGE_PAGE (Keyboard)
        0x19, 0xe0, //   USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7, //   USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00, //   LOGICAL_MINIMUM (0)
        0x25, 0x01, //   LOGICAL_MAXIMUM (1)
        0x75, 0x01, //   REPORT_SIZE (1)
        0x95, 0x08, //   REPORT_COUNT (8)
        0x81, 0x02, //   INPUT (Data,Var,Abs)
        0x95, 0x01, //   REPORT_COUNT (1)
        0x75, 0x08, //   REPORT_SIZE (8)
        0x81, 0x03, //   INPUT (Cnst,Var,Abs)
        0x95, 0x06, //   REPORT_COUNT (6)
        0x75, 0x08, //   REPORT_SIZE (8)
        0x15, 0x00, //   LOGICAL_MINIMUM (0)
        0x25, 0x73, //   LOGICAL_MAXIMUM (F24)
        0x05, 0x07, //   USAGE_PAGE (Keyboard)
        0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x73, //   USAGE_MAXIMUM (Keyboard F24)
        0x81, 0x00, //   INPUT (Data,Ary,Abs)
        0xc0,       // END_COLLECTION

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

        // application launch
        0x05, 0x0C,       // Usage Page (Consumer)
        0x09, 0x01,       // Usage (Consumer Control)
        0xA1, 0x01,       // Collection (Application)
        0x85, 0x04,       //   Report ID (4)
        0x15, 0x00,       //   Logical Minimum (0)
        0x25, 0x01,       //   Logical Maximum (1)
        0x75, 0x01,       //   Report Size (1)
        0x95, 0x08,       //   Report Count (8)
        0x0a, 0x85, 0x01, //   Usage (AL Text Editor)
        0x0a, 0x87, 0x01, //   Usage (AL Graphics Editor)
        0x0a, 0x92, 0x01, //   Usage (AL Calculator)
        0x0a, 0x96, 0x01, //   Usage (AL Internet Browser)
        0x0a, 0xA7, 0x01, //   Usage (AL Documents)
        0x0a, 0xB2, 0x01, //   Usage (AL Alarms)
        0x0a, 0xB3, 0x01, //   Usage (AL Clock)
        0x0a, 0xB4, 0x01, //   Usage (AL File Browser)
        0x81, 0x62,       //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0xC0,             // End Collection

        // system control
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x09, 0x80, // Usage  (System Control)
        0xa1, 0x01, // Collection (Application)
        0x85, 0x05, //   Report ID (5)
        0x75, 0x01, //   Report Size (1)
        0x95, 0x03, //   Report Count (3)
        0x15, 0x00, //   Logical Minimum (0)
        0x25, 0x01, //   Logical Maximum (1)
        0x09, 0x81, //   Usage (System Power)
        0x09, 0x82, //   Usage (System Sleep)
        0x09, 0x83, //   Usage (System Wake)
        0x81, 0x02, //	 Input (Data, Variable, Abs)
        0x75, 0x01, //   Report Size (1)
        0x95, 0x05, //   Report Count (5)
        0x81, 0x03, //   INPUT (Cnst,Var,Abs)
        0xc0,       // End Collection
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
        switch (report.reportType)
        {
        case ReportType::Keyboard:
        {
            uint8_t const keys[8] = {
                static_cast<uint8_t>(report.data[0]),
                0x00,
                static_cast<uint8_t>(report.data[1]),
                0,
                0,
                0,
                0,
                0,
            };
            HID().SendReport(2, keys, 8);
        }
        break;

        case ReportType::Media:
        case ReportType::SystemKey:
        case ReportType::ApplicationLaunch:
        {
            HID().SendReport(static_cast<uint8_t>(report.reportType), report.data, 1);
        }

        default:
            break;
        }
    }

    void MacroPad::releaseAll() const
    {
        uint8_t const bytes[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        HID().SendReport(2, bytes, 8);
        HID().SendReport(3, bytes, 1);
        HID().SendReport(4, bytes, 1);
        HID().SendReport(5, bytes, 1);
    }

} // namespace MacroPad

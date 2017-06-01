//
//
// The MIT License(MIT)
// 
// Copyright(c) 2015 by Karol Grzybowski
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
//
#pragma once
#ifndef _TileShell_Input_H__
#define _TileShell_Input_H__

#include <tileshell/required.hxx>

namespace TileShell::Input
{
    enum class KeyCode
    {
        KC_UNASSIGNED = 0x00,
        KC_ESCAPE = 0x01,
        KC_1 = 0x02,
        KC_2 = 0x03,
        KC_3 = 0x04,
        KC_4 = 0x05,
        KC_5 = 0x06,
        KC_6 = 0x07,
        KC_7 = 0x08,
        KC_8 = 0x09,
        KC_9 = 0x0A,
        KC_0 = 0x0B,
        KC_MINUS = 0x0C,
        KC_EQUALS = 0x0D,
        KC_BACK = 0x0E,
        KC_TAB = 0x0F,
        KC_Q = 0x10,
        KC_W = 0x11,
        KC_E = 0x12,
        KC_R = 0x13,
        KC_T = 0x14,
        KC_Y = 0x15,
        KC_U = 0x16,
        KC_I = 0x17,
        KC_O = 0x18,
        KC_P = 0x19,
        KC_LBRACKET = 0x1A,
        KC_RBRACKET = 0x1B,
        KC_RETURN = 0x1C,
        KC_LCONTROL = 0x1D,
        KC_A = 0x1E,
        KC_S = 0x1F,
        KC_D = 0x20,
        KC_F = 0x21,
        KC_G = 0x22,
        KC_H = 0x23,
        KC_J = 0x24,
        KC_K = 0x25,
        KC_L = 0x26,
        KC_SEMICOLON = 0x27,
        KC_APOSTROPHE = 0x28,
        KC_GRAVE = 0x29,
        KC_LSHIFT = 0x2A,
        KC_BACKSLASH = 0x2B,
        KC_Z = 0x2C,
        KC_X = 0x2D,
        KC_C = 0x2E,
        KC_V = 0x2F,
        KC_B = 0x30,
        KC_N = 0x31,
        KC_M = 0x32,
        KC_COMMA = 0x33,
        KC_PERIOD = 0x34,
        KC_SLASH = 0x35,
        KC_RSHIFT = 0x36,
        KC_MULTIPLY = 0x37,
        KC_LMENU = 0x38,
        KC_SPACE = 0x39,
        KC_CAPITAL = 0x3A,
        KC_F1 = 0x3B,
        KC_F2 = 0x3C,
        KC_F3 = 0x3D,
        KC_F4 = 0x3E,
        KC_F5 = 0x3F,
        KC_F6 = 0x40,
        KC_F7 = 0x41,
        KC_F8 = 0x42,
        KC_F9 = 0x43,
        KC_F10 = 0x44,
        KC_NUMLOCK = 0x45,
        KC_SCROLL = 0x46,
        KC_NUMPAD7 = 0x47,
        KC_NUMPAD8 = 0x48,
        KC_NUMPAD9 = 0x49,
        KC_SUBTRACT = 0x4A,
        KC_NUMPAD4 = 0x4B,
        KC_NUMPAD5 = 0x4C,
        KC_NUMPAD6 = 0x4D,
        KC_ADD = 0x4E,
        KC_NUMPAD1 = 0x4F,
        KC_NUMPAD2 = 0x50,
        KC_NUMPAD3 = 0x51,
        KC_NUMPAD0 = 0x52,
        KC_DECIMAL = 0x53,
        KC_OEM_102 = 0x56,
        KC_F11 = 0x57,
        KC_F12 = 0x58,
        KC_F13 = 0x64,
        KC_F14 = 0x65,
        KC_F15 = 0x66,
        KC_KANA = 0x70,
        KC_ABNT_C1 = 0x73,
        KC_CONVERT = 0x79,
        KC_NOCONVERT = 0x7B,
        KC_YEN = 0x7D,
        KC_ABNT_C2 = 0x7E,
        KC_NUMPADEQUALS = 0x8D,
        KC_PREVTRACK = 0x90,
        KC_AT = 0x91,
        KC_COLON = 0x92,
        KC_UNDERLINE = 0x93,
        KC_KANJI = 0x94,
        KC_STOP = 0x95,
        KC_AX = 0x96,
        KC_UNLABELED = 0x97,
        KC_NEXTTRACK = 0x99,
        KC_NUMPADENTER = 0x9C,
        KC_RCONTROL = 0x9D,
        KC_MUTE = 0xA0,
        KC_CALCULATOR = 0xA1,
        KC_PLAYPAUSE = 0xA2,
        KC_MEDIASTOP = 0xA4,
        KC_VOLUMEDOWN = 0xAE,
        KC_VOLUMEUP = 0xB0,
        KC_WEBHOME = 0xB2,
        KC_NUMPADCOMMA = 0xB3,
        KC_DIVIDE = 0xB5,
        KC_SYSRQ = 0xB7,
        KC_RMENU = 0xB8,
        KC_PAUSE = 0xC5,
        KC_HOME = 0xC7,
        KC_UP = 0xC8,
        KC_PGUP = 0xC9,
        KC_LEFT = 0xCB,
        KC_RIGHT = 0xCD,
        KC_END = 0xCF,
        KC_DOWN = 0xD0,
        KC_PGDOWN = 0xD1,
        KC_INSERT = 0xD2,
        KC_DELETE = 0xD3,
        KC_LWIN = 0xDB,
        KC_RWIN = 0xDC,
        KC_APPS = 0xDD,
        KC_POWER = 0xDE,
        KC_SLEEP = 0xDF,
        KC_WAKE = 0xE3,
        KC_WEBSEARCH = 0xE5,
        KC_WEBFAVORITES = 0xE6,
        KC_WEBREFRESH = 0xE7,
        KC_WEBSTOP = 0xE8,
        KC_WEBFORWARD = 0xE9,
        KC_WEBBACK = 0xEA,
        KC_MYCOMPUTER = 0xEB,
        KC_MAIL = 0xEC,
        KC_MEDIASELECT = 0xED,
    };

    struct KeyEventArgs
    {
        KeyCode     _key;
        uint32_t    _text;
    };

    enum class MouseButtonID
    {
        Left = 0,
        Right = 1,
        Middle = 2,
        Button3 = 3,
        Button4 = 4,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7
    };

    struct MouseEventArgs
    {
        ///
        /// Button bit mask.
        ///
        uint32_t _buttons;

        ///
        /// Relative X cursor coordinate.
        ///
        float32_t _relative_x;

        ///
        /// Relative Y cursor coordinate.
        ///
        float32_t _relative_y;

        ///
        /// Absolute X cursor coordinate.
        ///
        float32_t _absolute_x;

        ///
        /// Absolute Y cursor coordinate.
        ///
        float32_t _absolute_y;

        ///
        /// Determines whether mouse button is down.
        ///
        bool IsButtonDown(MouseButtonID id) const
        {
            return ((_buttons & (1 << static_cast<uint32_t>(id))) == 0) ? false : true;
        }
    };

    ///
    /// @brief
    ///     Keyboard event handler interface.
    ///
    /// @details
    ///     This interface declare methods used to handle keyboard events.
    ///
    class IKeyboardEventHandler
    {
    public:
        virtual ~IKeyboardEventHandler() { }

        ///
        /// @brief
        ///     Handles key down event.
        ///
        /// @param[in] e
        ///     An event args.
        ///
        /// @returns
        ///     true when handled, false otherwise.
        ///
        virtual bool OnKeyDown(const KeyEventArgs& e)
        {
            (void)e;
            return false;
        }

        ///
        /// @brief
        ///     Handles key up event.
        ///
        /// @param[in] e
        ///     An event args.
        ///
        /// @returns
        ///     true when handled, false otherwise.
        ///
        virtual bool OnKeyUp(const KeyEventArgs& e)
        {
            (void)e;
            return false;
        }
    };

    ///
    /// @brief
    ///     Mouse event handler interface.
    ///
    /// @details
    ///     This interface declare methods used to handle mouse events.
    ///
    class IMouseEventHandler
    {
    public:
        virtual ~IMouseEventHandler() { }

        ///
        /// @brief
        ///     Handles mouse down event.
        ///
        /// @param[in] e
        ///     An event args.
        ///
        /// @returns
        ///     true when handled, false otherwise.
        ///
        virtual bool OnMouseDown(const MouseEventArgs& e)
        {
            (void)e;
            return false;
        }

        ///
        /// @brief
        ///     Handles mouse move event.
        ///
        /// @param[in] e
        ///     An event args.
        ///
        /// @returns
        ///     true when handled, false otherwise.
        ///
        virtual bool OnMouseMove(const MouseEventArgs& e)
        {
            (void)e;
            return false;
        }

        ///
        /// @brief
        ///     Handles mouse up event.
        ///
        /// @param[in] e
        ///     An event args.
        ///
        /// @returns
        ///     true when handled, false otherwise.
        ///
        virtual bool OnMouseUp(const MouseEventArgs& e)
        {
            (void)e;
            return false;
        }
    };

}

#endif /* _TileShell_Input_H__ */
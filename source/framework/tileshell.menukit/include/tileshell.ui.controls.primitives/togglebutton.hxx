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

#include <tileshell.ui.controls.primitives/buttonbase.hxx>
#include <tileshell.serialization/typeserializer.hxx>

namespace TileShell::UI::Controls::Primitives
{
    ///
    /// @brief
    ///     This class implements two-state toggle button.
    ///
    class ToggleButton
        : public ButtonBase
    {
    protected:
        string_t        _text_checked;
        string_t        _text_unchecked;
        bool            _is_checked;

    public:
        ///
        /// @brief
        ///     Creates instance of the ToggleButton class.
        ///
        ToggleButton();

        ///
        /// @brief
        ///     Destroys instance of the ToggleButton class.
        ///
        virtual ~ToggleButton();

    public:
        ///
        /// @brief
        ///     Gets checked state.
        ///
        bool IsChecked() const;

        ///
        /// @brief
        ///     Sets checked state.
        ///
        void SetChecked(bool value);

        ///
        /// @brief
        ///     Gets enabled state text.
        ///
        const string_t& GetTextChecked() const;

        ///
        /// @brief
        ///     Sets enabled state text.
        ///
        void SetTextChecked(const string_t& value);

        ///
        /// @brief
        ///     Gets disabled state text.
        ///
        const string_t& GetTextUnchecked() const;

        ///
        /// @brief
        ///     Sets disabled state text.
        ///
        void GetTextUnchecked(const string_t& value);

    public:
        virtual bool Deserialize(Xml::XmlNode* node) override;
    };

    inline bool ToggleButton::IsChecked() const
    {
        return _is_checked;
    }

    inline void ToggleButton::SetChecked(bool value)
    {
        _is_checked = value;
        OnPropertyChanged(Core::StrongName("IsChecked"));
    }

    inline const string_t& ToggleButton::GetTextChecked() const
    {
        return _text_checked;
    }

    inline void ToggleButton::SetTextChecked(const string_t& value)
    {
        _text_checked = value;
        OnPropertyChanged(Core::StrongName("TextChecked"));
    }

    inline const string_t& ToggleButton::GetTextUnchecked() const
    {
        return _text_unchecked;
    }

    inline void ToggleButton::GetTextUnchecked(const string_t& value)
    {
        _text_unchecked = value;
        OnPropertyChanged(Core::StrongName("TextUnchecked"));
    }

}


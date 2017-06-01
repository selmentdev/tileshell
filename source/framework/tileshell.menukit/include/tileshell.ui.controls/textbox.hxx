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

#include <tileshell.ui.controls.primitives/textbase.hxx>
#include <tileshell.core/allocator.hxx>

namespace TileShell::UI::Controls
{

    class TextBox
        : public Primitives::TextBase
        , public Core::Allocator<TextBox>
    {
        TILESHELL_DECLARE_CONTROLFACTORYMETHOD(TextBox, "TextBox");
    private:
        Drawing::StyleItem9Grid _styleitem_background;
        Drawing::StyleItem9Grid _styleitem_hovered;
        size_t                  _caret_position_x;
        char                    _password_char;

    public:
        TextBox();
        virtual ~TextBox();

    public:
        bool DeleteNextChar();
        bool DeletePrevChar();
        bool MoveCaretNextChar();
        bool MoveCaretPrevChar();
        bool MoveCaretToBegin();
        bool MoveCaretToEnd();

    public:
        char GetPasswordChar() const;

        void SetPasswordChar(char value);

        size_t GetCaretPosition() const;

        size_t SetCaretPosition(size_t value);

    public:
        virtual bool Deserialize(Xml::XmlNode* node) override;
        virtual bool Update(float32_t delta) override;
        virtual bool GenerateGeometry(
            Drawing::GeometryBuilder& builder,
            GeometryType geometry_type) override;

    public:
        virtual bool OnPropertyChanged(const Core::StrongName& property_name) override;

    public:
        virtual bool OnKeyDown(const Input::KeyEventArgs& e) override;
        virtual bool OnKeyUp(const Input::KeyEventArgs& e) override;
        virtual bool OnMouseDown(const Input::MouseEventArgs& e) override;
        virtual bool OnMouseUp(const Input::MouseEventArgs& e) override;
        virtual bool OnMouseMove(const Input::MouseEventArgs& e) override;
    };

    inline char TextBox::GetPasswordChar() const
    {
        return _password_char;
    }

    inline void TextBox::SetPasswordChar(char value)
    {
        _password_char = value;
        OnPropertyChanged(Core::StrongName("PasswordChar"));
    }

    inline size_t TextBox::GetCaretPosition() const
    {
        return _caret_position_x;
    }

    inline size_t TextBox::SetCaretPosition(size_t value)
    {
        _caret_position_x = std::min(value, _text.size());
        OnPropertyChanged(Core::StrongName("CaretPosition"));
    }

}


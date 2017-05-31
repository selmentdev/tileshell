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
#include <TileShell/UI/Controls/TextBox.h>
//------------------------------------------------------------------------------------------------//
#define TILESHELL_CONTROL_TEXTBOX_STYLEITEM_BACKGROUND     "ButtonNormal"
#define TILESHELL_CONTROL_TEXTBOX_STYLEITEM_HOVERED        "ButtonHovered"
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
namespace Controls
{
//------------------------------------------------------------------------------------------------//
TextBox::TextBox()
    : TextBase()
    , _caret_position_x(0)
    , _password_char('\0')
{
}
//------------------------------------------------------------------------------------------------//
TextBox::~TextBox()
{
}
//------------------------------------------------------------------------------------------------//
bool TextBox::DeleteNextChar()
{
    // Caret position must be lesser, since we don't want to erase null terminator
    if (_caret_position_x < _text.size())
    {
        _text.erase(_text.begin() + _caret_position_x);
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
bool TextBox::DeletePrevChar()
{
    if ((_caret_position_x != 0) && (_caret_position_x <= _text.size()))
    {
        _text.erase(_text.begin() + _caret_position_x - 1);
        --_caret_position_x;
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
bool TextBox::MoveCaretNextChar()
{
    _caret_position_x = std::min(_caret_position_x + 1, _text.size());
    return true;
}
//------------------------------------------------------------------------------------------------//
bool TextBox::MoveCaretPrevChar()
{
    if (_caret_position_x != 0)
    {
        _caret_position_x = std::min(_caret_position_x - 1, _text.size());
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
bool TextBox::MoveCaretToBegin()
{
    _caret_position_x = 0;
    return true;
}
//------------------------------------------------------------------------------------------------//
bool TextBox::MoveCaretToEnd()
{
    _caret_position_x = _text.size();
    return true;
}
//------------------------------------------------------------------------------------------------//
bool TextBox::Deserialize(Xml::XmlNode* node)
{
    if (TextBase::Deserialize(node) == false)
    {
        return false;
    }

    using namespace Serialization;
    CharValueSerializer::Deserialize(_password_char, node->first_attribute("PasswordChar"));

    // Move caret after text
    _caret_position_x = _text.size();

    return true;
}
//------------------------------------------------------------------------------------------------//
bool TextBox::Update(float32_t delta)
{
    return TextBase::Update(delta);
}
//------------------------------------------------------------------------------------------------//
bool TextBox::GenerateGeometry(Drawing::GeometryBuilder& builder, GeometryType geometry_type)
{
    if (geometry_type == GeometryType_Static)
    {
        builder.DrawStyleItem(
            _global_transform_matrix,
            Drawing::Color(0xFFFFFFFF),
            _global_zorder,
            _rectangle, _padding,
            (_is_hovered || _is_focused) ? _styleitem_hovered : _styleitem_background);
    }
    else if (geometry_type == GeometryType_DynamicText)
    {

        string_t temporary(_text);

        if (_is_focused)
        {
            temporary.insert(_caret_position_x, 1, '_');
        }

        if (_password_char != '\0')
        {
            struct Pred
            {
                bool operator () (char value)
                {
                    return value != '|';
                }
            };

            std::replace_if(temporary.begin(), temporary.end(), Pred(), _password_char);
        }

        builder.DrawString(
            _global_transform_matrix,
            _text_color,
            _global_zorder,
            _rectangle,
            GetStyle()->GetFont(),
            temporary.c_str(),
            _font_size);
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool TextBox::OnPropertyChanged(const Core::StrongName& property_name)
{
    if (!TextBase::OnPropertyChanged(property_name))
    {
        return false;
    }

    if (property_name == Core::StrongName("Style"))
    {
        GetStyle()->GetItem(
            _styleitem_background,
            Core::StrongName(TILESHELL_CONTROL_TEXTBOX_STYLEITEM_BACKGROUND));
        GetStyle()->GetItem(
            _styleitem_hovered,
            Core::StrongName(TILESHELL_CONTROL_TEXTBOX_STYLEITEM_HOVERED));
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool TextBox::OnKeyDown(const Input::KeyEventArgs& e)
{
    if (e._key == Input::KC_BACK)
    {
        DeletePrevChar();
    }
    else if (e._key == Input::KC_DELETE)
    {
        DeleteNextChar();
    }
    else if (e._key == Input::KC_LEFT)
    {
        MoveCaretPrevChar();
    }
    else if (e._key == Input::KC_RIGHT)
    {
        MoveCaretNextChar();
    }
    else if (e._key == Input::KC_HOME)
    {
        MoveCaretToBegin();
    }
    else if (e._key == Input::KC_END)
    {
        MoveCaretToEnd();
    }
    else
    {
        char c = static_cast<char>(e._text);

        if (isprint(c))
        {
            tileshell_assert(_caret_position_x <= _text.length());

            _text.insert(_text.begin() + _caret_position_x, 1, c);
            ++_caret_position_x;
        }
    }


    return TextBase::OnKeyDown(e);
}
//------------------------------------------------------------------------------------------------//
bool TextBox::OnKeyUp(const Input::KeyEventArgs& e)
{
    return TextBase::OnKeyUp(e);
}
//------------------------------------------------------------------------------------------------//
bool TextBox::OnMouseDown(const Input::MouseEventArgs& e)
{
    return TextBase::OnMouseDown(e);
}
//------------------------------------------------------------------------------------------------//
bool TextBox::OnMouseUp(const Input::MouseEventArgs& e)
{
    return TextBase::OnMouseUp(e);
}
//------------------------------------------------------------------------------------------------//
bool TextBox::OnMouseMove(const Input::MouseEventArgs& e)
{
    return TextBase::OnMouseMove(e);
}
//------------------------------------------------------------------------------------------------//
}
}
}
//------------------------------------------------------------------------------------------------//
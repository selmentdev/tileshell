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
#include <TileShell/UI/Controls/CheckBox.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
namespace Controls
{
//------------------------------------------------------------------------------------------------//
#define TILESHELL_CONTROL_CHECKBOX_STYLEITEM_BACKGROUND     "CheckBoxNormal"
#define TILESHELL_CONTROL_CHECKBOX_STYLEITEM_HOVERED        "CheckBoxHovered"
#define TILESHELL_CONTROL_CHECKBOX_STYLEITEM_PUSHED         "CheckBoxPushed"
#define TILESHELL_CONTROL_CHECKBOX_STYLEITEM_DISABLED       "CheckBoxDisabled"
//------------------------------------------------------------------------------------------------//
CheckBox::CheckBox()
    : ToggleButton()
{
}
//------------------------------------------------------------------------------------------------//
CheckBox::~CheckBox()
{
}
//------------------------------------------------------------------------------------------------//
bool CheckBox::GenerateGeometry(Drawing::GeometryBuilder& out_builder, GeometryType geometry_type)
{
    if (geometry_type == GeometryType_Static)
    {
        out_builder.DrawStyleItem(
            _global_transform_matrix,
            Drawing::Color(1.0F, 1.0F, 1.0F, _opacity),
            _global_zorder,
            _rectangle, _padding,
            _is_enabled ? _styleitem_background : _styleitem_disabled);
    }
    else if (geometry_type == GeometryType_StaticText)
    {
        Drawing::Rect rect = _rectangle;
        rect.Width *= 0.5F;

        if (_is_checked)
        {
            rect.X += rect.Width;
        }

        out_builder.DrawString(
            _global_transform_matrix,
            _text_color,
            _global_zorder + 11.0F,
            rect,
            GetStyle()->GetFont(),
            _is_checked ? _text_checked.c_str() : _text_unchecked.c_str(),
            _font_size);
    }
    else if (geometry_type == GeometryType_Dynamic)
    {
        Drawing::Rect rect = _rectangle;
        rect.Width *= 0.5F;

        if (_is_checked)
        {
            rect.X += rect.Width;
        }

        out_builder.DrawStyleItem(
            _global_transform_matrix,
            Drawing::Color(1.0F, 1.0F, 1.0F, _opacity),
            _global_zorder + 10.0F,
            rect, _padding,
            _is_enabled ? (
                (_is_hovered || _is_focused) ?
                (_is_pushed ?
                 _styleitem_pushed :
                 _styleitem_hovered) :
                    _styleitem_background) :
                _styleitem_disabled
            );
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool CheckBox::OnPropertyChanged(const Core::StrongName& property_name)
{
    if (!ToggleButton::OnPropertyChanged(property_name))
    {
        return false;
    }

    if (property_name == Core::StrongName("Style"))
    {
        GetStyle()->GetItem(
            _styleitem_background,
            Core::StrongName(TILESHELL_CONTROL_CHECKBOX_STYLEITEM_BACKGROUND));
        GetStyle()->GetItem(
            _styleitem_hovered,
            Core::StrongName(TILESHELL_CONTROL_CHECKBOX_STYLEITEM_HOVERED));
        GetStyle()->GetItem(
            _styleitem_pushed,
            Core::StrongName(TILESHELL_CONTROL_CHECKBOX_STYLEITEM_PUSHED));
        GetStyle()->GetItem(
            _styleitem_disabled,
            Core::StrongName(TILESHELL_CONTROL_CHECKBOX_STYLEITEM_DISABLED));
    }
    else if (property_name == Core::StrongName("IsPushed"))
    {
        if (_is_pushed == true)
        {
            _is_checked = !_is_checked;

            if (_event_handler != nullptr)
            {
                _event_handler->OnStateChanged(this);
            }
        }
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
}
}
}
//------------------------------------------------------------------------------------------------//
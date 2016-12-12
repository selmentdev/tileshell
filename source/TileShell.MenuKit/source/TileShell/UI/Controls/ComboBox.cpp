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
#include <TileShell/UI/Controls/ComboBox.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
namespace Controls
{
//------------------------------------------------------------------------------------------------//
//#define TILESHELL_CONTROL_RESOURCE_SELECTBOX_STYLEITEM_BACKGROUND   "SelectBoxNormal"
#define TILESHELL_CONTROL_RESOURCE_COMBOBOX_STYLEITEM_BACKGROUND    "ButtonNormal"
#define TILESHELL_CONTROL_RESOURCE_COMBOBOX_STYLEITEM_UP_LEFT       "ArrowLeftUp"
#define TILESHELL_CONTROL_RESOURCE_COMBOBOX_STYLEITEM_UP_RIGHT      "ArrowRightUp"
#define TILESHELL_CONTROL_RESOURCE_COMBOBOX_STYLEITEM_DOWN_LEFT     "ArrowLeftDown"
#define TILESHELL_CONTROL_RESOURCE_COMBOBOX_STYLEITEM_DOWN_RIGHT    "ArrowRightDown"
//------------------------------------------------------------------------------------------------//
ComboBox::ComboBox()
    : SelectorBase()
    , _styleitem_background()
    , _styleitem_arrow_up_left()
    , _styleitem_arrow_up_right()
    , _styleitem_arrow_down_left()
    , _styleitem_arrow_down_right()
    , _rectangle_arrow_left()
    , _rectangle_arrow_right()
{
}
//------------------------------------------------------------------------------------------------//
ComboBox::~ComboBox()
{
}
//------------------------------------------------------------------------------------------------//
bool ComboBox::GenerateGeometry(Drawing::GeometryBuilder& out_builder, GeometryType geometry_type)
{
    if (geometry_type == GeometryType_Static)
    {
        out_builder.DrawStyleItem(
            _global_transform_matrix,
            Drawing::Color(1.0F, 1.0F, 1.0F, _opacity),
            _global_zorder,
            _rectangle, _padding,
            _styleitem_background);
    }
    else if (geometry_type == GeometryType_StaticText)
    {
        if (_is_expanded == false)
        {
            Drawing::Rect rect = _rectangle;

            const char* text = nullptr;

            if (_selected_item_index < _items.size())
            {
                text = _items[_selected_item_index]._text.c_str();
            }

            out_builder.DrawString(
                _global_transform_matrix,
                _text_color,
                _global_zorder + 11.0F,
                rect,
                GetStyle()->GetFont(),
                text != nullptr ? text : "No Items",
                _font_size);
        }
    }
    else if (geometry_type == GeometryType_DynamicText)
    {
        if (_is_expanded != false)
        {
            float32_t item_height = _rectangle.Height;

            Drawing::Rect rect = _rectangle;
            rect.Height *= _items.size();
            rect.SetCenter(_rectangle.GetCenter());

            for (Primitives::SelectorItemCollection::iterator it = _items.begin(), end = _items.end();
                 it != end;
                 ++it)
            {
                out_builder.DrawString(
                    _global_transform_matrix,
                    _text_color,
                    _global_zorder + 11.0F,
                    rect,
                    GetStyle()->GetFont(),
                    it->_text.c_str(),
                    _font_size);

                rect.Y += item_height;
            }
        }
    }
    else if (geometry_type == GeometryType_Dynamic)
    {
        if (_is_expanded != false)
        {
            Drawing::Rect rect = _rectangle;
            rect.Height *= _items.size();
            rect.SetCenter(_rectangle.GetCenter());

            out_builder.DrawStyleItem(
                _global_transform_matrix,
                Drawing::Color(1.0F, 1.0F, 1.0F, _opacity),
                _global_zorder + 10.0F,
                rect, _padding,
                _styleitem_background);
        }
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool ComboBox::OnPropertyChanged(const Core::StrongName& property_name)
{
    if (!SelectorBase::OnPropertyChanged(property_name))
    {
        return false;
    }

    if (property_name == Core::StrongName("Style"))
    {
        GetStyle()->GetItem(
            _styleitem_background,
            Core::StrongName(TILESHELL_CONTROL_RESOURCE_COMBOBOX_STYLEITEM_BACKGROUND));
        GetStyle()->GetItem(
            _styleitem_arrow_up_left,
            Core::StrongName(TILESHELL_CONTROL_RESOURCE_COMBOBOX_STYLEITEM_UP_LEFT));
        GetStyle()->GetItem(
            _styleitem_arrow_up_right,
            Core::StrongName(TILESHELL_CONTROL_RESOURCE_COMBOBOX_STYLEITEM_UP_RIGHT));
        GetStyle()->GetItem(
            _styleitem_arrow_down_left,
            Core::StrongName(TILESHELL_CONTROL_RESOURCE_COMBOBOX_STYLEITEM_DOWN_LEFT));
        GetStyle()->GetItem(
            _styleitem_arrow_down_right,
            Core::StrongName(TILESHELL_CONTROL_RESOURCE_COMBOBOX_STYLEITEM_DOWN_RIGHT));
    }
    else if (property_name == Core::StrongName("Transform"))
    {
        _rectangle_arrow_left = _rectangle;
        _rectangle_arrow_left.Width = _rectangle_arrow_left.Height;
        _rectangle_arrow_right = _rectangle_arrow_left;
        _rectangle_arrow_right.X = _rectangle.GetRight() - _rectangle_arrow_right.Width;
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool ComboBox::OnKeyDown(const Input::KeyEventArgs& e)
{
    return SelectorBase::OnKeyDown(e);
}
//------------------------------------------------------------------------------------------------//
bool ComboBox::OnKeyUp(const Input::KeyEventArgs& e)
{
    return SelectorBase::OnKeyUp(e);
}
//------------------------------------------------------------------------------------------------//
bool ComboBox::OnMouseDown(const Input::MouseEventArgs& e)
{
    return SelectorBase::OnMouseDown(e);
}
//------------------------------------------------------------------------------------------------//
bool ComboBox::OnMouseUp(const Input::MouseEventArgs& e)
{
    _is_expanded = !_is_expanded;

    return SelectorBase::OnMouseUp(e);
}
//------------------------------------------------------------------------------------------------//
bool ComboBox::OnMouseMove(const Input::MouseEventArgs& e)
{
    return SelectorBase::OnMouseMove(e);
}
//------------------------------------------------------------------------------------------------//
}
}
}
//------------------------------------------------------------------------------------------------//
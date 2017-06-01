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
#include <tileshell.ui.controls/multibutton.hxx>
#include <tileshell.ui.controls/menuscene.hxx>

#include <sstream>

namespace TileShell::UI::Controls
{

    MultiButton::MultiButton()
        : Primitives::ButtonBase()
        , _styleitem_item_selected()
        , _styleitem_item_pushed()
        , _items()
        , _item_size(20.0F, 100.0F)
        , _item_padding(5.0F, 5.0F, 5.0F, 5.0F)
        , _hover_elevate(50.0F)
        , _hover_elevate_min(25.0F)
        , _hover_elevate_max(50.0F)
        , _hover_elevate_speed(1.0F)
        , _counter(0.0F)
        , _hover_item_index(0)
        , _hover_item_color(1.0F, 1.0F, 1.0F, 1.0F)
        , _hover_item_background_color(1.0F, 1.0F, 1.0F, 1.0F)
        , _is_shift_down(false)
    {
    }

    MultiButton::~MultiButton()
    {
    }

    bool MultiButton::GenerateGeometry(Drawing::GeometryBuilder& out_builder,
        GeometryType geometry_type)
    {
        if (geometry_type == GeometryType::Dynamic)
        {
            if ((_hover_item_index < _items.size()) && (_is_focused || _is_hovered))
            {
                Drawing::Rect item_rect(_rectangle.X, _rectangle.Y, _item_size.Width, _item_size.Height);
                item_rect.Y += _hover_item_index * _item_size.Height;

                out_builder.DrawStyleItem(
                    _global_transform_matrix,
                    _hover_item_background_color,
                    _global_zorder + _hover_elevate,
                    item_rect,
                    _item_padding,
                    _is_pushed ? _styleitem_item_pushed : _styleitem_item_selected);
            }
        }
        else if (geometry_type == GeometryType::DynamicText)
        {
            Drawing::Rect item_rect(_rectangle.X, _rectangle.Y, _item_size.Width, _item_size.Height);
            item_rect.Deflate(_item_padding);

            for (size_t i = 0; i != _items.size(); ++i)
            {
                if ((i == _hover_item_index) && (_is_focused || _is_hovered))
                {
                    out_builder.DrawString(
                        _global_transform_matrix,
                        _hover_item_color,
                        _global_zorder + _hover_elevate,
                        item_rect,
                        GetStyle()->GetFont(),
                        _items[i]._text.c_str(),
                        _font_size,
                        Drawing::TextAlign_Left);
                }
                else
                {
                    out_builder.DrawString(
                        _global_transform_matrix,
                        _text_color,
                        _global_zorder,
                        item_rect,
                        GetStyle()->GetFont(),
                        _items[i]._text.c_str(),
                        _font_size,
                        Drawing::TextAlign_Left);
                }

                item_rect.Y += _item_size.Height;
            }
        }

        return true;
    }

    bool MultiButton::Deserialize(Xml::XmlNode* node)
    {
        if (Control::Deserialize(node) == false)
        {
            return false;
        }

        using namespace Serialization;

        string_t name;

        if (StringValueSerializer::Deserialize(name, node->first_attribute("SelectedItem")) == false)
        {
            return false;
        }

        if (GetStyle()->GetItem(_styleitem_item_selected, Core::StrongName::Create(name)) == false)
        {
            return false;
        }

        if (StringValueSerializer::Deserialize(name, node->first_attribute("PushedItem")) == false)
        {
            return false;
        }

        if (GetStyle()->GetItem(_styleitem_item_pushed, Core::StrongName::Create(name)) == false)
        {
            return false;
        }

        if (SizeValueSerializer::Deserialize(_item_size, node->first_attribute("ItemSize")) == false)
        {
            return false;
        }

        ThicknessValueSerializer::Deserialize(_item_padding, node->first_attribute("ItemPadding"));

        if (FloatValueSerializer::Deserialize(_hover_elevate,
            node->first_attribute("HoverElevate")) == false)
        {
            return false;
        }

        FloatValueSerializer::Deserialize(_hover_elevate_min, node->first_attribute("HoverElevateMin"));
        FloatValueSerializer::Deserialize(_hover_elevate_max, node->first_attribute("HoverElevateMax"));
        FloatValueSerializer::Deserialize(_hover_elevate_speed, node->first_attribute("HoverElevateSpeed"));

        ColorValueSerializer::Deserialize(_hover_item_color, node->first_attribute("HoverItemColor"));
        ColorValueSerializer::Deserialize(_hover_item_background_color,
            node->first_attribute("HoverItemBackgroundColor"));

        Xml::XmlNode* node_items = node->first_node("MultiButton.Items");

        if (node_items != nullptr)
        {
            Xml::XmlNode* node_item = node_items->first_node("Item");

            while (node_item != nullptr)
            {
                MultiButtonItem item;

                if (MultiButtonItemSerializer::Deserialize(item, node_item) == true)
                {
                    _items.push_back(item);
                }

                node_item = node_item->next_sibling();
            }

            struct MultiButtonItemSortPredicate
            {
                bool operator () (const MultiButtonItem& l, const MultiButtonItem& r) const
                {
                    return l._id < r._id;
                }
            };

            std::sort(_items.begin(), _items.end(), MultiButtonItemSortPredicate());
        }

        return true;
    }

    bool MultiButton::OnPropertyChanged(const Core::StrongName& property_name)
    {
        if (!ButtonBase::OnPropertyChanged(property_name))
        {
            return false;
        }

        return true;
    }

    bool MultiButton::OnKeyDown(const Input::KeyEventArgs& e)
    {
        if ((e._key == Input::KeyCode::KC_LSHIFT) || (e._key == Input::KeyCode::KC_RSHIFT))
        {
            _is_shift_down = true;
        }

        if (e._key == Input::KeyCode::KC_UP)
        {
            SelectPrevItem();
        }
        else if (e._key == Input::KeyCode::KC_DOWN)
        {
            SelectNextItem();
        }
        /*else if (e._key == Input::KC_TAB)
        {
            if (_is_shift_down)
            {
                if (CanSelectPrev())
                {
                    SelectPrevItem();
                }
            }
            else
            {
                if (CanSelectNext())
                {
                    SelectNextItem();
                }
            }
        }*/
        else if (e._key == Input::KeyCode::KC_HOME)
        {
            SelectFirstItem();
            return true;
        }
        else if (e._key == Input::KeyCode::KC_END)
        {
            SelectLastItem();
            return true;
        }

        if (e._key == Input::KeyCode::KC_RETURN)
        {
            _is_pushed = true;
        }

        return Control::OnKeyDown(e);
    }

    bool MultiButton::OnKeyUp(const Input::KeyEventArgs& e)
    {
        if ((e._key == Input::KeyCode::KC_LSHIFT) || (e._key == Input::KeyCode::KC_RSHIFT))
        {
            _is_shift_down = false;
        }

        if (e._key == Input::KeyCode::KC_RETURN)
        {
            _is_pushed = false;
            return DoAction();
        }

        /*else if (e._key == Input::KC_TAB)
        {
            // Prevent focusing next control
            return true;
        }*/

        return Control::OnKeyUp(e);
    }

    bool MultiButton::OnMouseDown(const Input::MouseEventArgs& e)
    {
        return Control::OnMouseDown(e);
    }

    bool MultiButton::OnMouseUp(const Input::MouseEventArgs& e)
    {
        DoAction();

        return Control::OnMouseUp(e);
    }

    bool MultiButton::OnMouseMove(const Input::MouseEventArgs& e)
    {
        Drawing::Rect item_rect(_rectangle.X, _rectangle.Y, _item_size.Width, _item_size.Height);

        //_hover_item_index = static_cast<size_t>(-1);
        size_t index_found = static_cast<size_t>(-1);

        for (size_t i = 0; i != _items.size(); ++i)
        {
            if (item_rect.Contains(e._absolute_x, e._absolute_y))
            {
                index_found = i;
                break;
            }

            item_rect.Y += _item_size.Height;
        }

        if (index_found != _hover_item_index)
        {
            _hover_item_index = index_found;
            _counter = 0.0F;
        }

        return Control::OnMouseMove(e);
    }

    bool MultiButton::OnMouseLeave()
    {
        _hover_item_index = static_cast<size_t>(-1);
        return ButtonBase::OnMouseLeave();
    }

    bool MultiButton::DoAction()
    {
        if ((_hover_item_index != ~0) && (_items.size() != 0))
        {
            if (_hover_item_index < _items.size())
            {
                _menu_scene->Navigate(_items[_hover_item_index]._activity);

                if (_event_handler != nullptr)
                {
                    this->SetTargetActivity(_items[_hover_item_index]._activity);
                    _event_handler->OnCommand(this);
                }

                return true;
            }
        }

        return false;
    }

    Control* MultiButton::GetNextLogicalControl(bool reverse) const
    {
        // Special case: iterate through items in menu select pane using Tab and Shift + Tab
        if (reverse == false)
        {
            //if (CanSelectNext())
            {
                // I know what I'm doing
                // TODO: Remove const from this method
                //return const_cast<MultiButton*>(this);
            }
        }
        else
        {
            //if (CanSelectPrev())
            {
                //return const_cast<MultiButton*>(this);
            }
        }

        return Control::GetNextLogicalControl(reverse);
    }

    bool MultiButton::GetSelectorRectangle(Drawing::Rect& out_result) const
    {
        if (_hover_item_index < _items.size())
        {
            Drawing::Rect item_rect(_rectangle.X, _rectangle.Y, _item_size.Width, _item_size.Height);
            item_rect.Y += _hover_item_index * _item_size.Height;
            out_result = item_rect;
            return true;
        }

        return false;
    }

    bool MultiButton::Update(float32_t delta)
    {
        if (!ButtonBase::Update(delta))
        {
            return false;
        }

        float32_t range = _hover_elevate_max - _hover_elevate_min;
        _counter += (delta * _hover_elevate_speed);

        _hover_elevate = _hover_elevate_min + range * std::sin(_counter);

        return true;
    }

}

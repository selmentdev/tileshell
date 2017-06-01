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
#include <tileshell.ui.controls/control.hxx>
#include <tileshell.serialization/typeserializer.hxx>
#include <tileshell.ui.controls/activity.hxx>
#include <tileshell.ui.controls/menuscene.hxx>
#include <tileshell.ui.controls.primitives/buttonbase.hxx>

namespace TileShell::UI::Controls
{

    Control::Control()
        : Visual()
        , _global_transform_matrix()
        , _global_zorder(0.0F)
        , _local_zorder(0.0F)
        , _control_parent(nullptr)
        , _control_next_sibling(nullptr)
        , _control_prev_sibling(nullptr)
        , _is_enabled(true)
        , _is_focusable(true)
        , _is_hovered(false)
        , _font_size(20.0F)
        , _text_color(1.0F, 1.0F, 1.0F, 1.0F)
        , _background_color(1.0F, 1.0F, 1.0F, 1.0F)
        , _menu_scene(nullptr)
        , _event_handler(nullptr)
        , _is_focused(false)
    {
    }

    Control::~Control()
    {
    }

    bool Control::Deserialize(Xml::XmlNode* node)
    {
        if (Visual::Deserialize(node) == false)
        {
            return false;
        }

        using namespace Serialization;

        BoolValueSerializer::Deserialize(_is_enabled, node->first_attribute("IsEnabled"));
        BoolValueSerializer::Deserialize(_is_focusable, node->first_attribute("IsFocusable"));
        FloatValueSerializer::Deserialize(_local_zorder, node->first_attribute("ZOrder"));
        FloatValueSerializer::Deserialize(_font_size, node->first_attribute("FontSize"));
        ColorValueSerializer::Deserialize(_text_color, node->first_attribute("TextColor"));
        ColorValueSerializer::Deserialize(_background_color, node->first_attribute("BackgroundColor"));
        return true;
    }

    bool Control::Update(float32_t delta)
    {
        (void)delta;

        return true;
    }

    bool Control::GenerateGeometry(Drawing::GeometryBuilder& out_builder, GeometryType geometry_type)
    {
        tileshell_unused(out_builder);
        tileshell_unused(geometry_type);
        return true;
    }

    bool Control::OnPropertyChanged(const Core::StrongName& property_name)
    {
        if (!Visual::OnPropertyChanged(property_name))
        {
            return false;
        }

        if (property_name == Core::StrongName("Transform"))
        {
            _global_transform_matrix = _local_transform_matrix;

            if (_control_parent != nullptr)
            {
                _global_transform_matrix.Multiply(
                    _control_parent->GetTransformMatrix(),
                    Drawing::MatrixOrder_Append);
            }

            _global_transform_matrix_inversed = _global_transform_matrix;
            _global_transform_matrix_inversed.Invert();
        }
        else if (property_name == Core::StrongName("ZOrder"))
        {
            _global_zorder = _local_zorder;

            if (_control_parent != nullptr)
            {
                //
                // Update actual ZOrder value
                //
                _global_zorder += _control_parent->GetGlobalZOrder();
            }
        }
        else if (property_name == Core::StrongName("Parent"))
        {
            this->OnPropertyChanged(Core::StrongName("ZOrder"));
            this->OnPropertyChanged(Core::StrongName("Transform"));
        }

        return true;
    }

    bool Control::OnMouseEnter()
    {
        _is_hovered = true;
        return true;
    }

    bool Control::OnMouseLeave()
    {
        _is_hovered = false;
        return true;
    }

    Control* Control::GetNextLogicalControl(bool reverse) const
    {
        // Possible bug: recurse calls to this method may generate stack overflow
        // At first, try next sibling...
        if (reverse == false)
        {
            if (_control_next_sibling != nullptr)
            {
                // If control is not focusable, skip it
                if (_control_next_sibling->_is_focusable == false)
                {
                    return _control_next_sibling->GetNextLogicalControl(false);
                }

                return _control_next_sibling;
            }
        }
        else
        {
            if (_control_prev_sibling != nullptr)
            {
                // If control is not focusable, skip it
                if (_control_prev_sibling->_is_focusable == false)
                {
                    return _control_prev_sibling->GetNextLogicalControl(true);
                }

                return _control_prev_sibling;
            }
        }

        // If we're last control, try our's parent instead
        if (_control_parent != nullptr)
        {
            return _control_parent->GetNextLogicalControl(reverse);
        }

        return nullptr;
    }

    Control* Control::HitTest(const Drawing::Point& point)
    {
#if 1
        auto inv = _local_transform_matrix;

        auto invxform_point = inv.TransformPoint(point.ToFloat32x2());

        return _rectangle.Contains(
            invxform_point.X,
            invxform_point.Y) ? this : nullptr;
#else
        return _rectangle.Contains(
            point.X,
            point.Y) ? this : nullptr;
#endif
    }

    bool Control::GetSelectorRectangle(Drawing::Rect& out_result) const
    {
        out_result = _rectangle;
        return true;
    }

}

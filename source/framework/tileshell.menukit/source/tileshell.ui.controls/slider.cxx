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
#include <tileshell.ui.controls/slider.hxx>

#define TILESHELL_CONTROL_RESOURCE_SLIDER_STYLEITEM_BACKGROUND      "ProgressBarNormal"
#define TILESHELL_CONTROL_RESOURCE_SLIDER_STYLEITEM_PROGRESS        "ProgressBarProgress"
#define TILESHELL_CONTROL_RESOURCE_SLIDER_STYLEITEM_HOVERED         "ButtonHovered"

namespace TileShell::UI::Controls
{

    Slider::Slider()
        : RangeBase()
        , _styleitem_background()
        , _styleitem_progress()
        , _is_lmb_down(false)
    {
    }

    Slider::~Slider()
    {
    }

    bool Slider::GenerateGeometry(Drawing::GeometryBuilder& out_builder, GeometryType geometry_type)
    {
        if (geometry_type == GeometryType::Static)
        {
            out_builder.DrawStyleItem(
                _global_transform_matrix,
                Drawing::Color(0xFFFFFFFF),
                _global_zorder,
                _rectangle, _padding,
                (_is_hovered || _is_focused)
                ? _styleitem_hovered
                : _styleitem_background);
        }
        else if (geometry_type == GeometryType::Dynamic)
        {
            Drawing::Rect progress = _rectangle;
            progress.Deflate(_padding);

            if (_orientation == Orientation::Horizontal)
            {
                progress.Width *= GetPercentage();
            }
            else
            {
                float32_t height = progress.Height;
                progress.Height *= GetPercentage();
                progress.Y += (height - progress.Height);
            }

            out_builder.DrawStyleItem(
                _global_transform_matrix,
                Drawing::Color(0xFFFFFFFF),
                _global_zorder + 10.0F,
                progress, Drawing::Thickness(0.0F, 0.0F, 0.0F, 0.0F),
                _styleitem_progress);
        }

        return true;
    }

    bool Slider::OnPropertyChanged(const Core::StrongName& property_name)
    {
        if (!RangeBase::OnPropertyChanged(property_name))
        {
            return false;
        }

        if (property_name == Core::StrongName("Style"))
        {
            GetStyle()->GetItem(
                _styleitem_background,
                Core::StrongName(TILESHELL_CONTROL_RESOURCE_SLIDER_STYLEITEM_BACKGROUND));
            GetStyle()->GetItem(
                _styleitem_hovered,
                Core::StrongName(TILESHELL_CONTROL_RESOURCE_SLIDER_STYLEITEM_HOVERED));
            GetStyle()->GetItem(
                _styleitem_progress,
                Core::StrongName(TILESHELL_CONTROL_RESOURCE_SLIDER_STYLEITEM_PROGRESS));
        }

        return true;
    }

    bool Slider::OnKeyDown(const Input::KeyEventArgs& e)
    {
        if ((e._key == Input::KeyCode::KC_LEFT) || (e._key == Input::KeyCode::KC_BACK))
        {
            Decrement(true);
        }
        else if (e._key == Input::KeyCode::KC_PGDOWN)
        {
            Decrement(false);
        }
        else if ((e._key == Input::KeyCode::KC_RIGHT) || (e._key == Input::KeyCode::KC_RETURN))
        {
            Increment(true);
        }
        else if (e._key == Input::KeyCode::KC_PGUP)
        {
            Increment(false);
        }
        else if (e._key == Input::KeyCode::KC_HOME)
        {
            SetValue(GetRangeMin());
        }
        else if (e._key == Input::KeyCode::KC_END)
        {
            SetValue(GetRangeMax());
        }
        else if (e._key == Input::KeyCode::KC_SPACE)
        {
            ResetValue();
        }

        return RangeBase::OnKeyDown(e);
    }

    bool Slider::OnKeyUp(const Input::KeyEventArgs& e)
    {
        return RangeBase::OnKeyUp(e);
    }

    bool Slider::OnMouseDown(const Input::MouseEventArgs& e)
    {
        if (e.IsButtonDown(Input::MouseButtonID::Left) == true)
        {
            _is_lmb_down = true;
        }

        return RangeBase::OnMouseDown(e);
    }

    bool Slider::OnMouseUp(const Input::MouseEventArgs& e)
    {
        _is_lmb_down = false;

        return RangeBase::OnMouseUp(e);
    }

    bool Slider::OnMouseMove(const Input::MouseEventArgs& e)
    {
        if (_is_lmb_down && _is_focused)
        {
            // Compute rect within progress
            Drawing::Rect progress = _rectangle;
            //progress.Deflate(_padding);

            float32_t value = 0.0F;

            if (_orientation == Orientation::Horizontal)
            {
                value = (e._absolute_x - progress.X) / progress.Width;  // value from range 0.0 to 1.0
            }
            else
            {
                value = (e._absolute_y - progress.Y) / progress.Height;  // value from range 0.0 to 1.0
            }

            SetValue(value * (_range_max - _range_min) + _range_min);
        }

        return RangeBase::OnMouseMove(e);
    }

    bool Slider::OnMouseLeave()
    {
        return RangeBase::OnMouseLeave();
    }

}


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

#include <tileshell.ui.controls/button.hxx>
#include <tileshell.ui.controls/activity.hxx>
#include <tileshell.ui.controls/menuscene.hxx>

namespace TileShell::UI::Controls
{

#define TILESHELL_CONTROL_BUTTON_STYLEITEM_BACKGROUND     "ButtonNormal"
#define TILESHELL_CONTROL_BUTTON_STYLEITEM_HOVERED        "ButtonHovered"
#define TILESHELL_CONTROL_BUTTON_STYLEITEM_PUSHED         "ButtonPushed"
#define TILESHELL_CONTROL_BUTTON_STYLEITEM_DISABLED       "ButtonDisabled"

    Button::Button()
        : Primitives::ButtonBase()
        , _styleitem_background()
        , _styleitem_hovered()
        , _styleitem_pushed()
        , _styleitem_disabled()
    {
    }

    Button::~Button()
    {
    }

    bool Button::Deserialize(Xml::XmlNode* node)
    {
        if (ButtonBase::Deserialize(node) == false)
        {
            return false;
        }

        using namespace Serialization;

        return true;
    }

    bool Button::Update(float32_t delta)
    {
        /*_transform.Rotate.Angle += delta;
        OnTransformChanged();
        */
        return ButtonBase::Update(delta);
    }

    bool Button::GenerateGeometry(Drawing::GeometryBuilder& builder, GeometryType geometry_type)
    {
        if (geometry_type == GeometryType::Static)
        {
            builder.DrawStyleItem(
                _global_transform_matrix,
                Drawing::Color(0xFFFFFFFF),
                _global_zorder,
                _rectangle, _padding,

                _is_enabled ? (
                (_is_hovered || _is_focused) ?
                    (_is_pushed ?
                        _styleitem_pushed :
                        _styleitem_hovered) :
                    _styleitem_background) :
                _styleitem_disabled
            );
        }
        else if (geometry_type == GeometryType::StaticText)
        {
            builder.DrawString(
                _global_transform_matrix,
                _text_color,
                _global_zorder,
                _rectangle,
                GetStyle()->GetFont(),
                _text.c_str(),
                _font_size);
        }

        return true;
    }

    bool Button::OnPropertyChanged(const Core::StrongName& property_name)
    {
        if (!ButtonBase::OnPropertyChanged(property_name))
        {
            return false;
        }

        if (property_name == Core::StrongName("IsPushed"))
        {
            if (_is_pushed == false)
            {
                if (_target_activity != Core::StrongName::Empty())
                {
                    _menu_scene->Navigate(_target_activity);
                }

                if (_event_handler != nullptr)
                {
                    _event_handler->OnCommand(this);
                }
            }
        }
        else if (property_name == Core::StrongName("Style"))
        {
            GetStyle()->GetItem(
                _styleitem_background,
                Core::StrongName(TILESHELL_CONTROL_BUTTON_STYLEITEM_BACKGROUND));
            GetStyle()->GetItem(
                _styleitem_hovered,
                Core::StrongName(TILESHELL_CONTROL_BUTTON_STYLEITEM_HOVERED));
            GetStyle()->GetItem(
                _styleitem_pushed,
                Core::StrongName(TILESHELL_CONTROL_BUTTON_STYLEITEM_PUSHED));
            GetStyle()->GetItem(
                _styleitem_disabled,
                Core::StrongName(TILESHELL_CONTROL_BUTTON_STYLEITEM_DISABLED));
        }

        return true;
    }

}


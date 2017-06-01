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

#include <tileshell.ui.controls/control.hxx>

namespace TileShell::UI::Controls
{

    inline const Drawing::Matrix& Control::GetGlobalTransformMatrix() const
    {
        return _global_transform_matrix;
    }

    inline float32_t Control::GetGlobalZOrder() const
    {
        return _global_zorder;
    }

    inline float32_t Control::GetZOrder() const
    {
        return _local_zorder;
    }

    inline void Control::SetZOrder(float32_t value)
    {
        _local_zorder = value;
        OnPropertyChanged(Core::StrongName("ZOrder"));
    }

    inline Control* Control::GetParent() const
    {
        return _control_parent;
    }

    inline void Control::SetParent(Control* value)
    {
        _control_parent = value;
        OnPropertyChanged(Core::StrongName("Parent"));
    }

    inline Control* Control::GetNextSibling() const
    {
        return _control_next_sibling;
    }

    inline Control* Control::GetPrevSibling() const
    {
        return _control_prev_sibling;
    }

    inline bool Control::IsEnabled() const
    {
        return _is_enabled;
    }

    inline void Control::SetEnabled(bool value)
    {
        _is_enabled = value;
        OnPropertyChanged(Core::StrongName("IsEnabled"));
    }

    inline bool Control::IsFocusable() const
    {
        return _is_focusable;
    }

    inline void Control::SetFocusable(bool value)
    {
        _is_focusable = value;
        OnPropertyChanged(Core::StrongName("IsFocusable"));
    }

    inline bool Control::IsHovered() const
    {
        return _is_hovered;
    }

    inline bool Control::IsFocused() const
    {
        return _is_focused;
    }

    inline void Control::SetFocused(bool value, bool reverse)
    {
        tileshell_unused(reverse);
        _is_focused = value;
        //OnFocusChanged(reverse);
        OnPropertyChanged(Core::StrongName("IsFocused"));
    }

    inline MenuScene* Control::GetScene() const
    {
        return _menu_scene;
    }

    inline void Control::SetScene(MenuScene* value)
    {
        _menu_scene = value;
    }

    inline IEventHandler* Control::GetEventHandler() const
    {
        return _event_handler;
    }

    inline void Control::SetEventHandler(IEventHandler* value)
    {
        _event_handler = value;
    }

    inline Control* Control::GetControlByName(const Core::StrongName& name)
    {
        if (_name == name)
        {
            return this;
        }

        return nullptr;
    }

    inline bool Control::IsChildControl(Control* control) const
    {
        tileshell_unused(control);
        return false;
    }

}


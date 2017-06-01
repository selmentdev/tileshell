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

#include <tileshell.ui.controls/activity.hxx>

namespace TileShell::UI::Controls
{

    inline const string_t& Activity::GetTitle() const
    {
        return _title;
    }

    inline void Activity::SetTitle(const char* value)
    {
        _title.assign(value);
        OnPropertyChanged(Core::StrongName("Title"));
    }

    inline const Core::StrongName& Activity::GetBacklink() const
    {
        return _backlink;
    }

    inline void Activity::SetBacklink(const Core::StrongName& value)
    {
        _backlink = value;
        OnPropertyChanged(Core::StrongName("Backlink"));
    }

    inline const ActivityCameraDesc& Activity::GetCameraDesc() const
    {
        return _camera;
    }

    inline void Activity::SetCameraDesc(const ActivityCameraDesc& value)
    {
        _camera = value;
        OnPropertyChanged(Core::StrongName("CameraDesc"));
    }

    inline const ActivityCameraPlacement& Activity::GetCameraPlacement() const
    {
        return _camera._placement;
    }

    inline void Activity::SetCameraPlacement(const ActivityCameraPlacement& value)
    {
        _camera._placement = value;
        OnPropertyChanged(Core::StrongName("CameraPlacement"));
    }

    inline Drawing::Size Activity::GetCursorSize() const
    {
        return _cursor_rect.GetSize();
    }

    inline Drawing::Point Activity::GetCursorLocation() const
    {
        return _cursor_rect.GetLocation();
    }

    inline void Activity::SetCursorSize(const Drawing::Size& value)
    {
        _cursor_rect.SetSize(value);
        OnPropertyChanged(Core::StrongName("CursorSize"));
    }

    inline void Activity::SetCursorLocation(const Drawing::Point& value)
    {
        _cursor_rect.SetLocation(value);
        OnPropertyChanged(Core::StrongName("CursorLocation"));
    }

    inline float32_t Activity::GetCursorZOrder() const
    {
        return _cursor_zorder;
    }

    inline void Activity::SetCursorZOrder(float32_t value)
    {
        _cursor_zorder = value;
        OnPropertyChanged(Core::StrongName("CursorZOrder"));
    }

}


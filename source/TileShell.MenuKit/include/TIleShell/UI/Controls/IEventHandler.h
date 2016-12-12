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

namespace TileShell
{
namespace UI
{
namespace Controls
{
class Activity;

namespace Primitives
{
class ButtonBase;
class TextBase;
class SelectorBase;
class RangeBase;
class ToggleButton;
}

///
/// @brief
///     Handles outgoing events.
///
struct IEventHandler
{
    virtual ~IEventHandler() { }

    virtual void OnCommand(Primitives::ButtonBase* control)
    {
        tileshell_unused(control);
    }

    virtual void OnTextChanged(Primitives::TextBase* control)
    {
        tileshell_unused(control);
    }

    virtual void OnSelectionChanged(Primitives::SelectorBase* control)
    {
        tileshell_unused(control);
    }

    virtual void OnValueChanged(Primitives::RangeBase* control)
    {
        tileshell_unused(control);
    }

    virtual void OnStateChanged(Primitives::ToggleButton* control)
    {
        tileshell_unused(control);
    }

    virtual void OnActivityEnter(Activity* activity)
    {
        tileshell_unused(activity);
    }

    virtual void OnActivityLeave(Activity* activity)
    {
        tileshell_unused(activity);
    }

    virtual void OnUpdate(Activity* activity, float32_t delta_time)
    {
        tileshell_unused(activity);
        tileshell_unused(delta_time);
    }
};

}
}
}

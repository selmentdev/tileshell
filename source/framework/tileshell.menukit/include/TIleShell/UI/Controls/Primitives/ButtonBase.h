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
//------------------------------------------------------------------------------------------------//
#include <TileShell/UI/Controls/Control.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
namespace Controls
{
namespace Primitives
{
///
/// Button state
///
enum ButtonState
{
    ///
    /// Default button state.
    ///
    ButtonState_Normal,

    ///
    /// Disabled button.
    ///
    ButtonState_Disabled,

    ///
    /// Checked button.
    ///
    ButtonState_Checked,

    ///
    /// Pushed button.
    ///
    ButtonState_Pushed,
};

///
/// @brief
///     Base class for buttons.
///
/// @remarks
///     Button base implements logic of button control.
///
/// @note
///     This control calls IEventHandler::OnCommand action.
///
/// @note
///     This control can navigate to another activity when clicked.
///
class ButtonBase
    : public Control
{
protected:
    ///
    /// Text displayed on button.
    ///
    string_t                _text;

    ///
    /// Target activity.
    ///
    /// @remarks
    ///     To disable auto navigation, set this to StrongName::Empty.
    ///
    Core::StrongName        _target_activity;

    ///
    /// Determines whether button is pushed down.
    ///
    bool                    _is_pushed;

public:
    ///
    /// Creates instance of the ButtonBase class.
    ///
    ButtonBase();

    ///
    /// Destroys instance of the ButtonBase class.
    ///
    virtual ~ButtonBase();

public:
    ///
    /// Gets button text.
    ///
    const string_t& GetText() const;

    ///
    /// Sets button text.
    ///
    void SetText(const string_t& value);

    ///
    /// Gets value indicating whether button is pushed down.
    ///
    bool IsPushed() const;

    ///
    /// Sets value indicating whether button is pushed down.
    ///
    void SetPushed(bool value);

    ///
    /// Gets strong name of target activity.
    ///
    Core::StrongName GetTargetActivity() const;

    ///
    /// Sets strong name of target activity.
    ///
    void SetTargetActivity(const Core::StrongName& value);

public:
    virtual bool Deserialize(Xml::XmlNode* node) override;

public:
    virtual bool OnKeyDown(const Input::KeyEventArgs& e) override;
    virtual bool OnKeyUp(const Input::KeyEventArgs& e) override;
    virtual bool OnMouseDown(const Input::MouseEventArgs& e) override;
    virtual bool OnMouseUp(const Input::MouseEventArgs& e) override;
    virtual bool OnMouseMove(const Input::MouseEventArgs& e) override;
};
//------------------------------------------------------------------------------------------------//
inline const string_t& ButtonBase::GetText() const
{
    return _text;
}
//------------------------------------------------------------------------------------------------//
inline void ButtonBase::SetText(const string_t& value)
{
    _text = value;
    OnPropertyChanged(Core::StrongName("Text"));
}
//------------------------------------------------------------------------------------------------//
inline bool ButtonBase::IsPushed() const
{
    return _is_pushed;
}
//------------------------------------------------------------------------------------------------//
inline void ButtonBase::SetPushed(bool value)
{
    _is_pushed = value;
    OnPropertyChanged(Core::StrongName("IsPushed"));
}
//------------------------------------------------------------------------------------------------//
inline Core::StrongName ButtonBase::GetTargetActivity() const
{
    return _target_activity;
}
//------------------------------------------------------------------------------------------------//
inline void ButtonBase::SetTargetActivity(const Core::StrongName& value)
{
    _target_activity = value;
    OnPropertyChanged(Core::StrongName("TargetActivity"));
}
//------------------------------------------------------------------------------------------------//
}
}
}
}
//------------------------------------------------------------------------------------------------//
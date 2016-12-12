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
#include <TileShell/UI/IScene.h>
#include <TileShell/UI/Controls/Activity.h>
#include <TileShell/Animation/Tween.h>
#include <TileShell/Core/Allocator.h>
#include <TileShell/UI/Controls/IEventHandler.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
class MenuScene
    : public IScene
    , public Core::Allocator<MenuScene>
{
protected:
    typedef std::vector<Controls::Activity*>    ActivityCollection;

protected:
    ActivityCollection                                          _activities;
    Controls::Activity*                                         _current_activity;
    Core::StrongName                                            _default_activity;
    Drawing::StyleRef                                           _style;
    bool                                                        _is_camera_moving;
    Animation::TweenLerp2<Controls::ActivityCameraPlacement>    _activity_placement_tween;

public:
    MenuScene();
    virtual ~MenuScene();

public:
    Controls::Activity* GetActivityByName(const Core::StrongName& name) const;

public:
    Controls::Activity* GetCurrentActivity() const;

    bool IsCameraMoving() const;

    bool GetCameraPlacement(Controls::ActivityCameraPlacement& out_result) const;

public:
    virtual bool Load(const string_t& path) override;
    virtual bool Draw(Drawing::IRenderFrameCallback* callback) override;
    virtual bool Update(float32_t delta) override;
    bool Deserialize(Xml::XmlNode* node);

    bool Navigate(const Core::StrongName& value);

public:
    virtual bool OnKeyDown(const Input::KeyEventArgs& e) override;
    virtual bool OnKeyUp(const Input::KeyEventArgs& e) override;
    virtual bool OnMouseDown(const Input::MouseEventArgs& e) override;
    virtual bool OnMouseUp(const Input::MouseEventArgs& e) override;
    virtual bool OnMouseMove(const Input::MouseEventArgs& e) override;
};
//------------------------------------------------------------------------------------------------//
inline Controls::Activity* MenuScene::GetCurrentActivity() const
{
    return _current_activity;
}
//------------------------------------------------------------------------------------------------//
inline bool MenuScene::IsCameraMoving() const
{
    return _is_camera_moving;
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
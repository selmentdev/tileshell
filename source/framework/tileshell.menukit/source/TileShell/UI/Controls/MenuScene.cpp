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
#include <TileShell/UI/Controls/MenuScene.h>
#include <TileShell/Drawing/Style.h>
#include <TileShell/Drawing/StyleManager.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
//------------------------------------------------------------------------------------------------//
MenuScene::MenuScene()
    : IScene()
    , _activities()
    , _current_activity(nullptr)
    , _default_activity()
    , _style()
    , _is_camera_moving(false)
{
}
//------------------------------------------------------------------------------------------------//
MenuScene::~MenuScene()
{
    for (ActivityCollection::iterator it = _activities.begin(), end = _activities.end();
         it != end;
         ++it)
    {
        delete *it;
    }

    _activities.clear();
}
//------------------------------------------------------------------------------------------------//
Controls::Activity* MenuScene::GetActivityByName(const Core::StrongName& name) const
{
    for (ActivityCollection::const_iterator it = _activities.begin(), end = _activities.end();
         it != end;
         ++it)
    {
        if ((*it)->GetName() == name)
        {
            return (*it);
        }
    }

    return nullptr;
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::Load(const string_t& path)
{
    Xml::XmlFile file(path.c_str());

    Xml::XmlDocument document;
    document.parse<0>(file.data());

    Xml::XmlNode* node = document.first_node("MenuScene");

    if (node == nullptr)
    {
        return false;
    }

    return Deserialize(node);
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::Draw(Drawing::IRenderFrameCallback* callback)
{
    for (ActivityCollection::iterator it = _activities.begin(), end = _activities.end();
         it != end;
         ++it)
    {
        (*it)->Draw(callback);
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::Update(float32_t delta)
{
    if (!_activity_placement_tween.IsEnd())
    {
        _activity_placement_tween.Increment(delta);
    }

    for (ActivityCollection::iterator it = _activities.begin(), end = _activities.end();
         it != end;
         ++it)
    {
        (*it)->Update(delta);
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::Deserialize(Xml::XmlNode* node)
{
    using namespace Serialization;

    if (StrongNameValueSerializer::Deserialize(_default_activity,
            node->first_attribute("DefaultActivity")) == false)
    {
        return false;
    }

    string_t style_name;

    if (StringValueSerializer::Deserialize(style_name, node->first_attribute("Style")) == false)
    {
        return false;
    }

    Drawing::StyleRef style = Drawing::StyleManager::GetStyle(style_name);

    Xml::XmlNode* item = node->first_node("Activity");

    while (item != nullptr)
    {
        Controls::Activity* activity = new Controls::Activity();
        activity->SetStyle(style);
        activity->SetScene(this);

        if (activity->Deserialize(item) != false)
        {
            _activities.push_back(activity);
        }
        else
        {
            delete activity;
            return false;
        }

        item = item->next_sibling("Activity");
    }

    Navigate(_default_activity);

    struct PredSortByZOrder
    {
        bool operator () (const Controls::Activity* lhs, const Controls::Activity* rhs) const
        {
            return lhs->GetGlobalZOrder() < rhs->GetGlobalZOrder();
        }
    };

    std::sort(_activities.begin(), _activities.end(), PredSortByZOrder());

    if (_current_activity == nullptr)
    {
        return false;
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::OnKeyDown(const Input::KeyEventArgs& e)
{
    if (!_activity_placement_tween.IsEnd())
    {
        return false;
    }

    if (_current_activity != nullptr)
    {
        _current_activity->OnKeyDown(e);
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::OnKeyUp(const Input::KeyEventArgs& e)
{
    if (!_activity_placement_tween.IsEnd())
    {
        return false;
    }

    if (_current_activity != nullptr)
    {
        _current_activity->OnKeyUp(e);
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::OnMouseDown(const Input::MouseEventArgs& e)
{
    if (!_activity_placement_tween.IsEnd())
    {
        return false;
    }

    if (_current_activity != nullptr)
    {
        _current_activity->OnMouseDown(e);
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::OnMouseUp(const Input::MouseEventArgs& e)
{
    if (!_activity_placement_tween.IsEnd())
    {
        return false;
    }

    if (_current_activity != nullptr)
    {
        _current_activity->OnMouseUp(e);
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::OnMouseMove(const Input::MouseEventArgs& e)
{
    if (!_activity_placement_tween.IsEnd())
    {
        return false;
    }

    if (_current_activity != nullptr)
    {
        _current_activity->OnMouseMove(e);
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::GetCameraPlacement(Controls::ActivityCameraPlacement& out_result) const
{
    if (_is_camera_moving == false)
    {
        if (!_activity_placement_tween.IsEnd())
        {
            _activity_placement_tween.Evaluate(out_result);
            return true;
        }

        if (_current_activity != nullptr)
        {
            _current_activity->GetCameraPlacementEx(out_result);
            //out_result = _current_activity->GetCameraPlacement();
            return true;
        }
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
bool MenuScene::Navigate(const Core::StrongName& value)
{
    UI::Controls::Activity* activity = GetActivityByName(value);

    // No current activity -> tween will be invalid
    if (_current_activity == nullptr)
    {
        _activity_placement_tween.Reset();
        _activity_placement_tween.Frames[0].KeyTime = 0.0F;
        _activity_placement_tween.Frames[1].KeyTime = 0.01F;

        activity->GetCameraPlacementEx(_activity_placement_tween.Frames[0].Value);
        activity->GetCameraPlacementEx(_activity_placement_tween.Frames[1].Value);
    }

    if (activity != nullptr)
    {
        if (_current_activity != nullptr)
        {
            _current_activity->OnActivityLeave();
            _current_activity->GetCameraPlacementEx(_activity_placement_tween.Frames[0].Value);
        }
        else
        {
            _activity_placement_tween.Evaluate(_activity_placement_tween.Frames[0].Value);
        }

        _activity_placement_tween.Frames[0].KeyTime = 0.0F;

        activity->GetCameraPlacementEx(_activity_placement_tween.Frames[1].Value);
        _activity_placement_tween.Frames[1].KeyTime = 0.75F;

        _activity_placement_tween.Reset();

        _current_activity = activity;

        _current_activity->OnActivityEnter();
    }

    return activity != nullptr;
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
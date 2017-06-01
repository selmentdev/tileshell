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
#include <tileshell.ui.controls.primitives/buttonbase.hxx>

namespace TileShell::UI::Controls::Primitives
{

    ButtonBase::ButtonBase()
        : _text()
        , _is_pushed(false)
    {
    }

    ButtonBase::~ButtonBase()
    {
    }

    bool ButtonBase::Deserialize(Xml::XmlNode* node)
    {
        if (Control::Deserialize(node) == false)
        {
            return false;
        }

        using namespace Serialization;

        //BoolValueSerializer::Deserialize(_is_checked, node->first_attribute("IsChecked"));
        StringValueSerializer::Deserialize(_text, node->first_attribute("Text"));
        StrongNameValueSerializer::Deserialize(_target_activity, node->first_attribute("TargetActivity"));

        return true;
    }

    bool ButtonBase::OnKeyDown(const Input::KeyEventArgs& e)
    {
        if (e._key == Input::KeyCode::KC_RETURN)
        {
            if (_is_pushed != true)
            {
                _is_pushed = true;
                OnPropertyChanged(Core::StrongName("IsPushed"));
            }
        }

        return Control::OnKeyDown(e);
    }

    bool ButtonBase::OnKeyUp(const Input::KeyEventArgs& e)
    {
        if (e._key == Input::KeyCode::KC_RETURN)
        {
            if (_is_pushed != false)
            {
                _is_pushed = false;
                OnPropertyChanged(Core::StrongName("IsPushed"));
            }
        }

        return Control::OnKeyUp(e);
    }

    bool ButtonBase::OnMouseDown(const Input::MouseEventArgs& e)
    {
        if (_is_pushed != true)
        {
            _is_pushed = true;
            OnPropertyChanged(Core::StrongName("IsPushed"));
        }

        return Control::OnMouseDown(e);
    }

    bool ButtonBase::OnMouseUp(const Input::MouseEventArgs& e)
    {
        if (_is_pushed != false)
        {
            _is_pushed = false;
            OnPropertyChanged(Core::StrongName("IsPushed"));
        }

        return Control::OnMouseUp(e);
    }

    bool ButtonBase::OnMouseMove(const Input::MouseEventArgs& e)
    {
        return Control::OnMouseMove(e);
    }

}


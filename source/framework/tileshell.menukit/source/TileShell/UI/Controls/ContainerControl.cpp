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
#include <TileShell/UI/Controls/ContainerControl.h>
#include <TileShell/UI/Controls/ControlFactory.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
namespace Controls
{
//------------------------------------------------------------------------------------------------//
ContainerControl::ContainerControl()
    : Control()
    , _control_first_child(nullptr)
{
}
//------------------------------------------------------------------------------------------------//
ContainerControl::~ContainerControl()
{
    Control* it = _control_first_child;

    while (it != nullptr)
    {
        Control* next = it->_control_next_sibling;
        delete it;
        it = next;
    }
}
//------------------------------------------------------------------------------------------------//
bool ContainerControl::AddControl(Control* control)
{
    if (IsChildControl(control) == false)
    {
        Control* last = _control_first_child;

        if (last != nullptr)
        {
            // Iterate to last control
            while (last->_control_next_sibling != nullptr)
            {
                last = last->_control_next_sibling;
            }

            // Set as last
            last->_control_next_sibling = control;
            control->_control_prev_sibling = last;
        }
        else
        {
            // set as first child. No children at all.
            _control_first_child = control;
            control->_control_prev_sibling = nullptr;
        }

        control->SetParent(this);
        control->_control_next_sibling = nullptr;

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
bool ContainerControl::RemoveControl(Control* control)
{
    if (IsChildControl(control) == true)
    {
        // Remove control from tree
        Control* prev = control->_control_prev_sibling;
        Control* next = control->_control_next_sibling;

        prev->_control_next_sibling = next;
        next->_control_prev_sibling = prev;

        // Erase control relation data
        control->_control_next_sibling = nullptr;
        control->_control_prev_sibling = nullptr;
        control->_control_parent = nullptr;

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
bool ContainerControl::Deserialize(Xml::XmlNode* node)
{
    if (Control::Deserialize(node) == false)
    {
        return false;
    }

    Xml::XmlNode* item = node->first_node();

    while (item != nullptr)
    {
        Control* control = ControlFactory::CreateInstance(Core::StrongName::Create(item->name()));

        if (control != nullptr)
        {
            control->_control_parent = this; // no onparentchanged call
            control->SetStyle(this->GetStyle());
            control->SetScene(this->GetScene());

            if (control->Deserialize(item) != false)
            {
                AddControl(control);
            }
            else
            {
                delete control;
                return false;
            }
        }

        item = item->next_sibling();
    }

    OnPropertyChanged(Core::StrongName("Transform"));
    OnPropertyChanged(Core::StrongName("ZOrder"));

    return true;
}
//------------------------------------------------------------------------------------------------//
bool ContainerControl::GenerateGeometry(
    Drawing::GeometryBuilder& out_builder,
    GeometryType geometry_type)
{
    for (Control* it = _control_first_child; it != nullptr; it = it->_control_next_sibling)
    {
        it->GenerateGeometry(out_builder, geometry_type);
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool ContainerControl::Update(float32_t delta)
{
    for (Control* it = _control_first_child; it != nullptr; it = it->_control_next_sibling)
    {
        it->Update(delta);
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
void ContainerControl::SetEventHandler(IEventHandler* value)
{
    Control::SetEventHandler(value);

    Control* c = _control_first_child;

    while (c != nullptr)
    {
        c->SetEventHandler(value);
        c = c->_control_next_sibling;
    }
}
//------------------------------------------------------------------------------------------------//
bool ContainerControl::OnControlAdded()
{
    return true;
}
//------------------------------------------------------------------------------------------------//
bool ContainerControl::OnControlRemoved()
{
    return true;
}
//------------------------------------------------------------------------------------------------//
bool ContainerControl::OnPropertyChanged(const Core::StrongName& property_name)
{
    if (!Control::OnPropertyChanged(property_name))
    {
        return false;
    }

    if ((property_name == Core::StrongName("Transform")) ||
        (property_name == Core::StrongName("ZOrder")))
    {
        //
        // Update each children control
        //
        for (Control* it = _control_first_child; it != nullptr; it = it->_control_next_sibling)
        {
            it->OnPropertyChanged(property_name);
        }
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool ContainerControl::IsChildControl(Control* control) const
{
    Control* it = _control_first_child;

    while (it != nullptr)
    {
        if (it == control || it->IsChildControl(control) == true)
        {
            return true;
        }

        it = it->_control_next_sibling;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
Control* ContainerControl::GetNextLogicalControl(bool reverse) const
{
    // Special case
    if (reverse == false)
    {
        Control* child = GetFirstChildControl();

        if (child != nullptr)
        {
            // Try get NLC from first child
            Control* c = child->GetNextLogicalControl(false);

            if (c == this)
            {
                return child;
            }

            return c;
        }
    }
    else
    {
        Control* child = GetLastChildControl();

        if (child != nullptr)
        {
            Control* c = child->GetNextLogicalControl(true);

            if (c == this)
            {
                return child;
            }

            return c;
        }
    }

    return Control::GetNextLogicalControl(reverse);
}
//------------------------------------------------------------------------------------------------//
Control* ContainerControl::HitTest(const Drawing::Point& point)
{
    Control* it = _control_first_child;

    while (it != nullptr)
    {
        if (it->HitTest(point) != nullptr)
        {
            return it;
        }

        it = it->_control_next_sibling;
    }

    return Control::HitTest(point);
}
//------------------------------------------------------------------------------------------------//
}
}
}
//------------------------------------------------------------------------------------------------//
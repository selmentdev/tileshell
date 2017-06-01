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

    class ContainerControl : public Control
    {
        friend class Control;
    protected:
        Control*        _control_first_child;

    public:
        ContainerControl();
        virtual ~ContainerControl();

    public:
        bool AddControl(Control* control);
        bool RemoveControl(Control* control);

    public:
        Control* GetFirstChildControl() const;

        Control* GetLastChildControl() const;

        virtual Control* GetControlByName(const Core::StrongName& name) override;

    public:
        virtual bool Deserialize(Xml::XmlNode* node) override;
        virtual bool GenerateGeometry(
            Drawing::GeometryBuilder& out_builder,
            GeometryType geometry_type) override;
        virtual bool Update(float32_t delta) override;

        virtual void SetEventHandler(IEventHandler* value) override;

    public:
        virtual bool OnControlAdded();
        virtual bool OnControlRemoved();

        virtual bool OnPropertyChanged(const Core::StrongName& property_name) override;

    public:
        virtual Control* GetNextLogicalControl(bool reverse = false) const override;
        virtual Control* HitTest(const Drawing::Point& point) override;

    protected:
        virtual bool IsChildControl(Control* control) const override;
    };

    inline Control* ContainerControl::GetFirstChildControl() const
    {
        return _control_first_child;
    }

    inline Control* ContainerControl::GetLastChildControl() const
    {
        Control* c = _control_first_child;

        if (c != nullptr)
        {
            while (c->_control_next_sibling != nullptr)
            {
                c = c->_control_next_sibling;
            }

            return c;
        }

        return nullptr;
    }

    inline Control* ContainerControl::GetControlByName(const Core::StrongName& name)
    {
        Control* c = _control_first_child;

        while (c != nullptr)
        {
            if (c->GetName() == name)
            {
                return c;
            }

            c = c->_control_next_sibling;
        }

        return Control::GetControlByName(name);
    }

}


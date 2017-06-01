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

#include <tileshell.ui/visual.hxx>
#include <tileshell.input/input.hxx>
#include <tileshell.serialization/typeserializer.hxx>
#include <tileshell.ui.controls/ieventhandler.hxx>

#define TILESHELL_DECLARE_CONTROLFACTORYMETHOD(_Class, _Identifier) \
    public: \
    __forceinline static TileShell::Core::StrongName GetTypeName() \
    { \
        return TileShell::Core::StrongName(_Identifier); \
    } \
    \
    __forceinline static TileShell::UI::Controls::Control* CreateInstance() \
    { \
        return new _Class(); \
    }

namespace TileShell::UI
{
    class MenuScene;
}
namespace TileShell::UI::Controls
{
    enum class Orientation
    {
        Horizontal,
        Vertical,
    };

    enum class HorizontalAlignment
    {
        Left,
        Center,
        Right,
    };

    enum class VerticalAlignment
    {
        Top,
        Center,
        Bottom,
    };


    ///
    /// Control object.
    ///
    /// @detailed
    ///     This class declares methods and properties available in all visual controls. It also
    ///     maintains controls hierarchy and cache parent-related transformations
    ///
    /// @note
    ///     Possible optimization: each concrete Control class implementation should use own control
    ///     styles instead. ControlStyle is an implementation which can generate geometry of specific
    ///     control and can be shared between groups of controls of the same type. Thus, ControlStyle
    ///     implementation handles rendering separately from data storage and logic. But for now
    ///     current Primitives are sufficient.
    ///
    class Control
        : public Visual
        , public Input::IKeyboardEventHandler
        , public Input::IMouseEventHandler
    {
        friend class ContainerControl;
    protected:
        Drawing::Matrix         _global_transform_matrix;
        Drawing::Color          _text_color;
        Drawing::Color          _background_color;
        Drawing::Matrix         _global_transform_matrix_inversed;
        float32_t               _global_zorder;
        float32_t               _local_zorder;
        Control*                _control_parent;
        Control*                _control_next_sibling;
        Control*                _control_prev_sibling;
        MenuScene*              _menu_scene;
        IEventHandler*          _event_handler;
        float32_t               _font_size;
        bool                    _is_enabled;
        bool                    _is_focusable;
        bool                    _is_hovered;
        bool                    _is_focused;

    public:
        Control();
        virtual ~Control();

    public:
        const Drawing::Matrix& GetGlobalTransformMatrix() const;

        float32_t GetGlobalZOrder() const;

        float32_t GetZOrder() const;

        void SetZOrder(float32_t value);

        Control* GetParent() const;

        void SetParent(Control* value);

        Control* GetNextSibling() const;

        Control* GetPrevSibling() const;

        bool IsEnabled() const;

        void SetEnabled(bool value);

        bool IsFocusable() const;

        void SetFocusable(bool value);

        bool IsHovered() const;

        bool IsFocused() const;

        void SetFocused(bool value, bool reverse = false);

        MenuScene* GetScene() const;

        void SetScene(MenuScene* value);

        IEventHandler* GetEventHandler() const;

        virtual void SetEventHandler(IEventHandler* value);

        virtual Control* GetControlByName(const Core::StrongName& name);

    public:
        virtual bool Deserialize(Xml::XmlNode* node) override;
        virtual bool Update(float32_t delta) override;

        virtual bool GenerateGeometry(
            Drawing::GeometryBuilder& out_builder,
            GeometryType goemetry_type) override;

        virtual bool GetSelectorRectangle(Drawing::Rect& out_result) const;

    public:
        virtual bool OnPropertyChanged(const Core::StrongName& property_name) override;

        virtual bool OnMouseEnter();
        virtual bool OnMouseLeave();

    public:
        virtual Control* GetNextLogicalControl(bool reverse = false) const;

        ///
        /// Performs planar hit test, using global transform matrix.
        ///
        /// @param[in] point
        ///     A point.
        ///
        /// @returns
        ///     true when successful, false otherwise.
        ///
        virtual Control* HitTest(const Drawing::Point& point);

    protected:
        virtual bool IsChildControl(Control* control) const;
    };

}

namespace TileShell::Serialization
{
    template <>
    struct ValueSerializer<UI::Controls::Orientation>
    {
        static bool Deserialize(UI::Controls::Orientation& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            if (_stricmp(attr->value(), "Horizontal") == 0)
            {
                out_result = UI::Controls::Orientation::Horizontal;
                return true;
            }
            else if (_stricmp(attr->value(), "Vertical") == 0)
            {
                out_result = UI::Controls::Orientation::Vertical;

                return true;
            }

            return false;
        }
    };

    template <>
    struct ValueSerializer<UI::Controls::HorizontalAlignment>
    {
        static bool Deserialize(UI::Controls::HorizontalAlignment& out_result,
            const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            if (_stricmp(attr->value(), "Left") == 0)
            {
                out_result = UI::Controls::HorizontalAlignment::Left;
                return true;
            }
            else if (_stricmp(attr->value(), "Center") == 0)
            {
                out_result = UI::Controls::HorizontalAlignment::Center;

                return true;
            }
            else if (_stricmp(attr->value(), "Right") == 0)
            {
                out_result = UI::Controls::HorizontalAlignment::Right;

                return true;
            }

            return false;
        }
    };

    template <>
    struct ValueSerializer<UI::Controls::VerticalAlignment>
    {
        static bool Deserialize(UI::Controls::VerticalAlignment& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            if (_stricmp(attr->value(), "Top") == 0)
            {
                out_result = UI::Controls::VerticalAlignment::Top;
                return true;
            }
            else if (_stricmp(attr->value(), "Center") == 0)
            {
                out_result = UI::Controls::VerticalAlignment::Center;

                return true;
            }
            else if (_stricmp(attr->value(), "Bottom") == 0)
            {
                out_result = UI::Controls::VerticalAlignment::Bottom;

                return true;
            }

            return false;
        }
    };

}

#include <tileshell.ui.controls/control.inl.hxx>


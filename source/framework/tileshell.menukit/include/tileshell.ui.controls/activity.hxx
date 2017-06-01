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
#include <tileshell.ui/ielement.hxx>
#include <tileshell.ui.controls/control.hxx>
#include <tileshell.ui.controls/containercontrol.hxx>
#include <tileshell.drawing/style.hxx>
#include <tileshell.drawing/irenderframecallback.hxx>
#include <tileshell.drawing/geometrybuffer.hxx>
#include <tileshell.animation/tween.hxx>
#include <tileshell.core/allocator.hxx>

namespace TileShell::UI::Controls
{

    ///
    /// @brief
    ///     Activity internal state.
    ///
    enum class ActivityState : uint32_t
    {
        UpdateGeometryStatic = 1 << 0,
        UpdateGeometryDynamic = 1 << 1,
        UpdateTextStatic = 1 << 2,
        UpdateTextDynamic = 1 << 3,
        UpdateText = UpdateTextStatic | UpdateTextDynamic,
        UpdateGeometry = UpdateGeometryStatic | UpdateGeometryDynamic,
        UpdateAll = UpdateText | UpdateGeometry,
    };
    TILESHELL_ENUM_CLASS_FLAGS(ActivityState);

    ///
    /// @brief
    ///     Activity camera placement.
    ///
    struct ActivityCameraPlacement
    {
        ///
        /// Camera position
        ///
        float32x3_t                 _position;

        ///
        /// Camera target point
        ///
        float32x3_t                 _target;

        ///
        /// Rotation angle around axis lying on target and position points
        ///
        float32x3_t                 _up;

        ///
        /// @brief
        ///     Gets activity scaling value.
        ///
        float32_t GetScale() const
        {
            return std::abs(_target.Z - _position.Z);
        }
    };

    ///
    /// @brief
    ///     Activity camera descriptor.
    ///
    /// @details
    ///     This struct describes camera placement.
    ///
    struct ActivityCameraDesc
    {
        ActivityCameraPlacement     _placement;
    };

    ///
    /// @brief
    ///     Activity control.
    ///
    /// @details
    ///     Activity represents single focused thing that user can do. It's abstraction of window from
    ///     desktop interfaces.
    ///
    class Activity
        : public ContainerControl
        , public Core::Allocator<Activity>
    {
    protected:
        string_t                    _title;
        Core::StrongName            _backlink;
        Drawing::StyleItem9Grid     _style_element_activity;
        Drawing::StyleItem9Grid     _style_element_activity_header;
        Drawing::StyleItem9Grid     _style_element_selector;
        Control*                    _selected_control;
        Control*                    _hovered_control;
        ActivityState               _state;
        ActivityCameraDesc          _camera;
        Drawing::Rect               _cursor_rect;
        Drawing::StyleItem1Quad     _cursor_style_element;
        float32_t                   _cursor_zorder;
        bool                        _is_shift_down;
        bool                        _has_background;

    protected:
        Drawing::GeometryBufferRef  _geometry_text_static;
        Drawing::GeometryBufferRef  _geometry_text_dynamic;
        Drawing::GeometryBufferRef  _geometry_static;
        Drawing::GeometryBufferRef  _geometry_dynamic;

    public:
        ///
        /// @brief
        ///     Creates instance of the Activity class.
        ///
        Activity();

        ///
        /// @brief
        ///     Destroys instance of the Activity class.
        ///
        virtual ~Activity();

    public:
        ///
        /// @brief
        ///     Sets activity title.
        ///
        const string_t& GetTitle() const;

        ///
        /// @brief
        ///     Gets activity title.
        ///
        void SetTitle(const char* value);

        ///
        /// @brief
        ///     Gets activity backlink.
        ///
        const Core::StrongName& GetBacklink() const;

        ///
        /// @brief
        ///     Sets activity backlink.
        ///
        void SetBacklink(const Core::StrongName& value);

        ///
        /// @brief
        ///     Gets camera descriptor.
        ///
        const ActivityCameraDesc& GetCameraDesc() const;

        ///
        /// @brief
        ///     Sets camera descriptor.
        ///
        void SetCameraDesc(const ActivityCameraDesc& value);

        ///
        /// @brief
        ///     Gets camera placement.
        ///
        const ActivityCameraPlacement& GetCameraPlacement() const;

        ///
        /// Gets camera placement for tilt view.
        ///
        /// @param[out] out_result
        ///     A target camera placement after tilt.
        ///
        void GetCameraPlacementEx(ActivityCameraPlacement& out_result) const;

        ///
        /// @brief
        ///     Sets camera placement.
        ///
        void SetCameraPlacement(const ActivityCameraPlacement& value);

        ///
        /// @brief
        ///     Gets cursor size.
        ///
        Drawing::Size GetCursorSize() const;

        ///
        /// @brief
        ///     Sets cursor size.
        ///
        Drawing::Point GetCursorLocation() const;

        ///
        /// @brief
        ///     Sets cursor size.
        ///
        void SetCursorSize(const Drawing::Size& value);

        ///
        /// @brief
        ///     Sets cursor location.
        ///
        void SetCursorLocation(const Drawing::Point& value);

        ///
        /// @brief
        ///     Gets cursor z-order.
        ///
        float32_t GetCursorZOrder() const;

        ///
        /// @brief
        ///     Sets cursor z-order.
        ///
        void SetCursorZOrder(float32_t value);

    public:
        virtual bool Deserialize(Xml::XmlNode* node) override;
        virtual bool Update(float32_t delta) override;
        virtual bool GenerateGeometry(
            Drawing::GeometryBuilder& builder,
            GeometryType geometry_type) override;
        bool Draw(Drawing::IRenderFrameCallback* callback);

    public:
        virtual bool OnPropertyChanged(const Core::StrongName& property_name) override;

        virtual bool OnAddControl();
        virtual bool OnRemoveControl();
        virtual bool OnActivityEnter();
        virtual bool OnActivityLeave();

    public:
        ///
        /// @brief
        ///     Gets next logical control.
        ///
        /// @param[in] reverse
        ///     Determines direction of control traversal.
        ///
        virtual Control* GetNextLogicalControl(bool reverse = false) const override;

        // Overridden internal event handlers
    public:
        virtual bool OnKeyDown(const Input::KeyEventArgs& e) override;
        virtual bool OnKeyUp(const Input::KeyEventArgs& e) override;
        virtual bool OnMouseDown(const Input::MouseEventArgs& e) override;
        virtual bool OnMouseUp(const Input::MouseEventArgs& e) override;
        virtual bool OnMouseMove(const Input::MouseEventArgs& e) override;
    };

}

namespace TileShell::Animation
{

    template<>
    inline void Lerp<UI::Controls::ActivityCameraPlacement>(
        UI::Controls::ActivityCameraPlacement& out_result,
        const UI::Controls::ActivityCameraPlacement& value1,
        const UI::Controls::ActivityCameraPlacement& value2,
        float32_t t)
    {
        Lerp(out_result._position, value1._position, value2._position, t);
        Lerp(out_result._target, value1._target, value2._target, t);
        Lerp(out_result._up, value1._up, value2._up, t);
    }

}

#include <tileshell.ui.controls/activity.inl.hxx>


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
#include <tileshell.ui.controls/activity.hxx>
#include <tileshell.drawing/resourcefactory.hxx>
#include <tileshell.drawing/stylemanager.hxx>
#include <tileshell.ui.controls/controlfactory.hxx>
#include <tileshell.ui.controls/menuscene.hxx>

namespace TileShell::UI::Controls
{

    Activity::Activity()
        : _title()
        , _backlink()
        , _style_element_activity()
        , _style_element_activity_header()
        , _style_element_selector()
        , _selected_control(nullptr)
        , _hovered_control(nullptr)
        , _state(ActivityState::UpdateAll)
        , _is_shift_down(false)
        , _camera()
        , _cursor_rect(0.0F, 0.0F, 64.0F, 64.0F)
        , _cursor_style_element()
        , _cursor_zorder(1.0F)
        , _geometry_text_static()
        , _geometry_text_dynamic()
        , _geometry_static()
        , _has_background(false)
    {
        _geometry_static = Drawing::ResourceFactory::CreateGeometryBuffer();
        _geometry_dynamic = Drawing::ResourceFactory::CreateGeometryBuffer();
        _geometry_text_static = Drawing::ResourceFactory::CreateGeometryBuffer();
        _geometry_text_dynamic = Drawing::ResourceFactory::CreateGeometryBuffer();
    }

    Activity::~Activity()
    {
    }

    bool Activity::Deserialize(Xml::XmlNode* node)
    {
        using namespace Serialization;

        string_t name;

        //
        // Get style element for activity
        //
        if (StringValueSerializer::Deserialize(name, node->first_attribute("StyleElement")) == false)
        {
            _has_background = false;
        }

        if (_style->GetItem(_style_element_activity, Core::StrongName::Create(name)) != false)
        {
            _has_background = true;
        }

        //
        // Get style element for activity header
        //
        if (StringValueSerializer::Deserialize(name, node->first_attribute("StyleElementHeader")) == false)
        {
            //return false;
        }

        _style->GetItem(_style_element_selector, Core::StrongName::Create("ActivitySelector"));
        _style->GetItem(_style_element_activity_header, Core::StrongName::Create(name));

        //
        // Get title
        //
        StringValueSerializer::Deserialize(_title, node->first_attribute("Title"));

        //
        // Get camera position, up vector and target
        //
        Float32x3ValueSerializer::Deserialize(
            _camera._placement._position,
            node->first_attribute("CameraPosition"));
        Float32x3ValueSerializer::Deserialize(
            _camera._placement._target,
            node->first_attribute("CameraTarget"));
        Float32x3ValueSerializer::Deserialize(
            _camera._placement._up,
            node->first_attribute("CameraUp"));

        Drawing::Size cursor_size(32.0F, 32.0F);
        SizeValueSerializer::Deserialize(cursor_size, node->first_attribute("CursorSize"));
        _cursor_rect.SetSize(cursor_size);

        FloatValueSerializer::Deserialize(_cursor_zorder, node->first_attribute("CursorZOrder"));

        StrongNameValueSerializer::Deserialize(_backlink, node->first_attribute("Backlink"));

        if (ContainerControl::Deserialize(node) == false)
        {
            return false;
        }

        //
        // Update cursor position to center
        //
        _cursor_rect.SetLocation(_rectangle.GetCenter());

        _style->GetItem(_cursor_style_element, Core::StrongName("Cursor"));

        return true;
    }

    bool Activity::Update(float32_t delta)
    {
        if (_event_handler != nullptr)
        {
            _event_handler->OnUpdate(this, delta);
        }

        if (ContainerControl::Update(delta) == false)
        {
            return false;
        }

        // DEBUG: Remove from release
        _state |= ActivityState::UpdateAll;

        //
        // Update static geometry
        //
        if ((_state & ActivityState::UpdateGeometryStatic) != ActivityState::UpdateGeometryStatic)
        {
            Drawing::GeometryBuilder builder;
            builder.Begin();

            GenerateGeometry(builder, GeometryType::Static);

            builder.End(_geometry_static);

            _state &= ~ActivityState::UpdateGeometryStatic;
        }

        //
        // Update static geometry
        //
        if ((_state & ActivityState::UpdateGeometryDynamic) != ActivityState::UpdateGeometryDynamic)
        {
            Drawing::GeometryBuilder builder;
            builder.Begin();

            GenerateGeometry(builder, GeometryType::Dynamic);

            builder.End(_geometry_dynamic);

            _state &= ~ActivityState::UpdateGeometryDynamic;
        }

        //
        // Update static text geometry
        //
        if ((_state & ActivityState::UpdateTextStatic) != ActivityState::UpdateTextStatic)
        {
            Drawing::GeometryBuilder builder;
            builder.Begin();

            GenerateGeometry(builder, GeometryType::StaticText);

            builder.End(_geometry_text_static);

            _state &= ~ActivityState::UpdateTextStatic;
        }

        //
        // Update dynamic text geometry.
        //
        if ((_state & ActivityState::UpdateTextDynamic) != ActivityState::UpdateTextDynamic)
        {
            Drawing::GeometryBuilder builder;
            builder.Begin();

            GenerateGeometry(builder, GeometryType::DynamicText);

            builder.End(_geometry_text_dynamic);

            _state &= ~ActivityState::UpdateTextDynamic;
        }

        return true;
    }

    bool Activity::GenerateGeometry(Drawing::GeometryBuilder& builder, GeometryType geometry_type)
    {
        //
        // Generate activity specific geometry
        //
        if (geometry_type == GeometryType::Static)
        {
            if (_has_background)
            {
                // Draw activity.
                builder.DrawStyleItem(
                    _global_transform_matrix,
                    Drawing::Color(0xFFFFFFFF),
                    _global_zorder,
                    _rectangle, _padding,
                    _style_element_activity);
            }
        }
        else if (geometry_type == GeometryType::Dynamic)
        {
            Drawing::Rect cursor = _cursor_rect;
            float32_t scale = GetCameraPlacement().GetScale();

            Drawing::Size size = _rectangle.GetSize();

            cursor.Width = (cursor.Width / size.Height) * scale;
            cursor.Height = (cursor.Height / size.Height) * scale;

            // Draw cursor.
            builder.DrawStyleItem(
                _global_transform_matrix,
                Drawing::Color(0xFFFFFFFF),
                _global_zorder + _cursor_zorder,
                cursor,
                _cursor_style_element);

            /*if (_selected_control != nullptr)
            {
                Drawing::Rect rc;
                if (_selected_control->GetSelectorRectangle(rc))
                {
                    rc.Inflate(_selected_control->GetPadding());

                    builder.DrawStyleItem(
                        _global_transform_matrix,
                        Drawing::Color(0xFFFFFFFF),
                        _global_zorder + 2.0F,
                        rc, _selected_control->GetPadding(),
                        _style_element_selector);
                }
            }*/
        }
        else  if (geometry_type == GeometryType::StaticText)
        {
            /*builder.DrawString(
                _global_transform_matrix,
                Drawing::Color(1.0F, 1.0F, 1.0F, 1.0F),
                _global_zorder,
                _rectangle,
                GetStyle()->GetFont(),
                _title.c_str(),
                _font_size);*/
        }

        return ContainerControl::GenerateGeometry(builder, geometry_type);
    }

    bool Activity::Draw(Drawing::IRenderFrameCallback* callback)
    {
        callback->DoRender(_geometry_static, _style->GetTexture(), _geometry_static->GetVertexCount());

        callback->DoRender(_geometry_text_static, _style->GetFont()->GetTexture(),
            _geometry_text_static->GetVertexCount());
        callback->DoRender(_geometry_text_dynamic, _style->GetFont()->GetTexture(),
            _geometry_text_dynamic->GetVertexCount());

        callback->DoRender(_geometry_dynamic, _style->GetTexture(), _geometry_dynamic->GetVertexCount());

        return true;
    }

    bool Activity::OnAddControl()
    {
        return true;
    }

    bool Activity::OnRemoveControl()
    {
        return true;
    }

    Control* Activity::GetNextLogicalControl(bool reverse) const
    {
        Control* result = GetFirstChildControl();

        // Override this beharviour. Activity has no parent and no siblings
        if (reverse != false)
        {
            result = GetLastChildControl();
        }

        if (result->IsFocusable() == false)
        {
            result = result->GetNextLogicalControl(reverse);
        }

        return result;
    }

    bool Activity::OnPropertyChanged(const Core::StrongName& property_name)
    {
        if (!ContainerControl::OnPropertyChanged(property_name))
        {
            return false;
        }

        return true;
    }

    bool Activity::OnKeyDown(const Input::KeyEventArgs& e)
    {
        if ((e._key == Input::KeyCode::KC_LSHIFT) || (e._key == Input::KeyCode::KC_RSHIFT))
        {
            _is_shift_down = true;
        }

        // Behaviour: if there's no focused control, select first one
        if (_selected_control == nullptr)
        {
            _selected_control = this->_control_first_child;
        }

        // Pass event to selected control
        if (_selected_control != nullptr)
        {
            return _selected_control->OnKeyDown(e);
        }

        return IKeyboardEventHandler::OnKeyDown(e);
    }

    bool Activity::OnKeyUp(const Input::KeyEventArgs& e)
    {
        // Back to previous activity has priority
        if (e._key == Input::KeyCode::KC_ESCAPE)
        {
            _menu_scene->Navigate(_backlink);

            return true;
        }
        else if ((e._key == Input::KeyCode::KC_LSHIFT) || (e._key == Input::KeyCode::KC_RSHIFT))
        {
            _is_shift_down = false;
        }
        else if (e._key == Input::KeyCode::KC_TAB)
        {
            if (_selected_control != nullptr)
            {
                Control* next = _selected_control->GetNextLogicalControl(_is_shift_down);

                if ((next != nullptr) && (next != _selected_control))
                {
                    _selected_control->SetFocused(false, _is_shift_down);

                    _selected_control = next;

                    _selected_control->SetFocused(true, !_is_shift_down);
                }
            }
        }

        // Pass event to selected control
        if (_selected_control != nullptr)
        {
            return _selected_control->OnKeyUp(e);
        }

        return IKeyboardEventHandler::OnKeyUp(e);
    }

    bool Activity::OnMouseDown(const Input::MouseEventArgs& e)
    {
        Control* control = HitTest(_cursor_rect.GetLocation());

        if ((control != nullptr) && (control != this))
        {
            Input::MouseEventArgs args = e;
            args._absolute_x = _cursor_rect.X;
            args._absolute_y = _cursor_rect.Y;
            control->OnMouseDown(args);

            if (_selected_control != nullptr)
            {
                _selected_control->SetFocused(false);
            }

            _selected_control = control;

            if (_selected_control != nullptr)
            {
                _selected_control->SetFocused(true);
            }
        }

        return true;
    }

    bool Activity::OnMouseUp(const Input::MouseEventArgs& e)
    {
        Control* control = HitTest(_cursor_rect.GetLocation());

        if ((control != nullptr) && (control != this))
        {
            Input::MouseEventArgs args = e;
            args._absolute_x = _cursor_rect.X;
            args._absolute_y = _cursor_rect.Y;
            control->OnMouseUp(args);

            _selected_control = control;
        }

        return true;
    }

    bool Activity::OnMouseMove(const Input::MouseEventArgs& e)
    {
        // Update internal cursor position
        const float32_t scale = GetCameraPlacement().GetScale() * 0.0035F;
        _cursor_rect.X += e._relative_x * scale;
        _cursor_rect.Y += e._relative_y * scale;
        _cursor_rect.SetLocation(_rectangle.Clamp(_cursor_rect.GetLocation()));

        // Get affected control
        Control* control = HitTest(_cursor_rect.GetLocation());

        // We won't work on activity itself
        if ((control != nullptr) && (control != this))
        {
            // Disable hover state on currently hovered control
            if (_hovered_control != control)
            {
                // Unhover hovered control
                if (_hovered_control != nullptr)
                {
                    _hovered_control->OnMouseLeave();
                }

                // Unhover selected control
                if ((_selected_control != nullptr) && (_selected_control != _hovered_control))
                {
                    _selected_control->OnMouseLeave();
                }

                _hovered_control = control;
                control->OnMouseEnter();
            }

            Input::MouseEventArgs args = e;
            args._absolute_x = _cursor_rect.X;
            args._absolute_y = _cursor_rect.Y;
            control->OnMouseMove(args);
        }
        else
        {
            // Unhover hovered control
            if (_hovered_control != nullptr)
            {
                _hovered_control->OnMouseLeave();
                _hovered_control = nullptr;
            }

            // Unhover selected control
            if ((_selected_control != nullptr) && (_selected_control != _hovered_control))
            {
                _selected_control->OnMouseLeave();
            }
        }

        return IMouseEventHandler::OnMouseMove(e);
    }

    bool Activity::OnActivityEnter()
    {
        // If there's no focused control by default
        if (_selected_control == nullptr)
        {
            // Try get first focusable control
            if (_control_first_child != nullptr)
            {
                // First, try with first child
                _selected_control = _control_first_child;

                // And if it's not focusable, try next
                if (_selected_control->IsFocusable() == false)
                {
                    _selected_control = _selected_control->GetNextLogicalControl();
                }
            }

            // Try focus control
            if (_selected_control != nullptr)
            {
                _selected_control->SetFocused(true);
            }
        }

        return true;
    }

    bool Activity::OnActivityLeave()
    {
        if (_selected_control != nullptr)
        {
            _selected_control->SetFocused(false);
            _selected_control = nullptr;
        }

        return true;
    }

    void Activity::GetCameraPlacementEx(ActivityCameraPlacement& out_result) const
    {
        const float32_t scale = GetCameraPlacement().GetScale();
        const Drawing::Point r_center = _rectangle.GetCenter();
        const Drawing::Point c_center = _cursor_rect.GetLocation();

        Drawing::Size size = _rectangle.GetSize();

        Drawing::Point relative(
            c_center.X - r_center.X,
            c_center.Y - r_center.Y);

        relative.X /= size.Width * 0.5F;
        relative.Y /= size.Height * 0.5F;

        relative.X *= scale * 0.1F;
        relative.Y *= scale * 0.1F;

        out_result = _camera._placement;
        out_result._position.X += relative.X;
        out_result._position.Y -= relative.Y;
    }

}

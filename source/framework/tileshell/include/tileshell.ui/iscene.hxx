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

#include <tileshell.core/reference.hxx>
#include <tileshell.core/referenced.hxx>
#include <tileshell.drawing/irenderframecallback.hxx>
#include <tileshell.input/input.hxx>
#include <tileshell.drawing/size.hxx>

namespace TileShell::UI
{
    ///
    /// Scene State.
    ///
    /// @note
    ///     This enumeration represents internal scene state.
    enum SceneState
    {
        ///
        /// Update static text.
        ///
        SceneState_UpdateStaticText = 1 << 0,

        ///
        /// Update dynamic text.
        ///
        SceneState_UpdateDynamicText = 1 << 1,

        ///
        /// Updates geometry.
        ///
        SceneState_UpdateGeometry = 1 << 2,

        ///
        /// Updates all geometry.
        ///
        SceneState_UpdateAllGeometry =
        SceneState_UpdateStaticText |
        SceneState_UpdateDynamicText |
        SceneState_UpdateGeometry,
    };

    ///
    /// @brief
    ///     IScene interface.
    ///
    struct IScene
        : public Core::Referenced
        , public Input::IKeyboardEventHandler
        , public Input::IMouseEventHandler
    {
    protected:
        uint32_t        _scene_state;
        Drawing::Size   _screen_size;

    public:
        IScene()
            : _scene_state(0)
            , _screen_size(640.0F, 320.0F)
        {
        }

        virtual ~IScene() { }

    public:
        ///
        /// @brief
        ///     Loads scene from path.
        ///
        /// @returns
        ///     true when successful, false otherwise.
        ///
        virtual bool Load(const string_t& path) = 0;

        ///
        /// @brief
        ///     Draws scene.
        ///
        /// @param[in] callback
        ///     A render frame callback provided by engine./
        //
        /// @returns
        ///     true when successful, false otherwise.
        ///
        virtual bool Draw(Drawing::IRenderFrameCallback* callback) = 0;

        ///
        /// @brief
        ///     Updates scene.
        ///
        /// @param[in] delta
        ///     A time since last frame, in seconds.
        ///
        /// @returns
        ///     true when successful, false otherwise.
        ///
        virtual bool Update(float32_t delta) = 0;

    public:
        ///
        /// @brief
        ///     Gets screen size.
        ///
        Drawing::Size GetScreenSize() const
        {
            return _screen_size;
        }

        ///
        /// @brief
        ///     Sets screen size.
        ///
        void SetScreenSize(const Drawing::Size& value)
        {
            _screen_size = value;
        }

    public:
        ///
        /// Notifies scene that it should update itself.
        ///
        bool NotifyUpdateSceneState(UI::SceneState state)
        {
            _scene_state |= state;
        }
    };

    typedef Core::Reference<IScene> ISceneRef;
}
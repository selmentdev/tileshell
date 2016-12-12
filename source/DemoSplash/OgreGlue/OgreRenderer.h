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
#ifndef _OgreGlue_OgreRenderer_H__
#define _OgreGlue_OgreRenderer_H__
//------------------------------------------------------------------------------------------------//
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreRenderSystem.h>
#include <OgreViewport.h>
#include <OgreWindowEventUtilities.h>
#include <OgreRenderQueueListener.h>
//------------------------------------------------------------------------------------------------//
#include <TileShell/Drawing/IRenderFrameCallback.h>
#include <TileShell/UI/IScene.h>
//------------------------------------------------------------------------------------------------//
namespace OgreGlue
{

class OgreRenderer
    : public Ogre::RenderQueueListener
    , public TileShell::Drawing::IRenderFrameCallback
{
private:
    TileShell::UI::ISceneRef                    _scene;
    Ogre::RenderSystem*                         _render_system;
    Ogre::LayerBlendModeEx                      _color_blend_mode;
    Ogre::LayerBlendModeEx                      _alpha_blend_mode;
    Ogre::TextureUnitState::UVWAddressingMode   _texture_address_mode;
    size_t                                      _draw_calls;
    size_t                                      _vertices_count;
    float32_t                                   _scale;
    Ogre::Matrix4                               _world_matrix;
    bool                                        _wireframe;

public:
    OgreRenderer();
    virtual ~OgreRenderer();

    virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation,
                                    bool& skipThisInvocation) override;
    virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation,
                                  bool& repeatThisInvocation) override;

    //virtual void DoRender(const TileShell::Drawing::Matrix4x4& world_matrix, TileShell::Drawing::GeometryBufferRef gbuffer, TileShell::Drawing::TextureRef texture, size_t vertex_count) override;
    virtual void DoRender(
        TileShell::Drawing::GeometryBufferRef gbuffer,
        TileShell::Drawing::TextureRef texture, size_t vertex_count) override;

    virtual void DoRenderScreen(
        TileShell::Drawing::GeometryBufferRef gbuffer,
        TileShell::Drawing::TextureRef texture, size_t vertex_count) override;

    size_t GetDrawCalls() const
    {
        return _draw_calls;
    }
    size_t GetVertexCount() const
    {
        return _vertices_count;
    }

    void BeginRender();
    void EndRender();

public:
    void SetWireframe(bool value)
    {
        _wireframe = value;
    }

    bool GetWireframe() const
    {
        return _wireframe;
    }

    void SetScene(TileShell::UI::ISceneRef scene)
    {
        _scene = scene;
    }

    float32_t GetScale() const
    {
        return _scale;
    }

    void SetScale(float32_t value);
};
//------------------------------------------------------------------------------------------------//
}
//------------------------------------------------------------------------------------------------//
#endif /* _OgreGlue_OgreRenderer_H__ */
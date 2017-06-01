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
#ifndef _OgreGlue_OgreVertexBuffer_H__
#define _OgreGlue_OgreVertexBuffer_H__

#include <TileShell/Drawing/GeometryBuffer.h>

#include <OgreHardwareBufferManager.h>
#include <OgreHardwareVertexBuffer.h>
#include <OgrePrerequisites.h>
#include <OgreRenderOperation.h>
#include <OgreRenderSystem.h>
#include <OgreTextureManager.h>
#include <OgreTextureUnitState.h>

namespace OgreGlue
{
class OgreVertexBuffer : public TileShell::Drawing::GeometryBuffer
{
private:
    size_t                                  _vertex_count;
    size_t                                  _required_vertex_count;
    Ogre::RenderOperation                   _render_operation;
    Ogre::HardwareVertexBufferSharedPtr     _vertex_buffer;

private:
    void CreateVertexBuffer();
    void DestroyVertexBuffer();
    void ResizeVertexBuffer();

public:
    OgreVertexBuffer();
    virtual ~OgreVertexBuffer();

public:
    virtual void SetVertexCount(size_t count) override;
    virtual size_t GetVertexCount() const override;

    virtual TileShell::Drawing::Vertex* Map() override;
    virtual void Unmap() override;

    Ogre::RenderOperation* GetRenderOperation()
    {
        return &_render_operation;
    }

};
}

#endif /* _OgreGlue_OgreVertexBuffer_H__ */
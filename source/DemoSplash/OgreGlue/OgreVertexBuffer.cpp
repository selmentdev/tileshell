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
#include "OgreVertexBuffer.h"

namespace OgreGlue
{

OgreVertexBuffer::OgreVertexBuffer()
    : _vertex_count(30)
    , _required_vertex_count(0)
{
    CreateVertexBuffer();
}

OgreVertexBuffer::~OgreVertexBuffer()
{
    DestroyVertexBuffer();
}

void OgreVertexBuffer::CreateVertexBuffer()
{
    _render_operation.vertexData        = new Ogre::VertexData();
    _render_operation.vertexData->vertexStart = 0;

    Ogre::VertexDeclaration* vd = _render_operation.vertexData->vertexDeclaration;
    vd->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);

    vd->addElement(0, Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3), Ogre::VET_COLOUR,
                   Ogre::VES_DIFFUSE);
    vd->addElement(0, Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3) +
                   Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR), Ogre::VET_FLOAT2,
                   Ogre::VES_TEXTURE_COORDINATES);

    _vertex_buffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
                         _render_operation.vertexData->vertexDeclaration->getVertexSize(0),
                         _vertex_count,
                         Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE,
                         false);

    _render_operation.vertexData->vertexBufferBinding->setBinding(0, _vertex_buffer);
    _render_operation.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
    _render_operation.useIndexes = false;
}

void OgreVertexBuffer::DestroyVertexBuffer()
{
    delete _render_operation.vertexData;
    _render_operation.vertexData = nullptr;
    _vertex_buffer.setNull();
}

void OgreVertexBuffer::ResizeVertexBuffer()
{
    _vertex_count = _required_vertex_count + 30;
    DestroyVertexBuffer();
    CreateVertexBuffer();
}

void OgreVertexBuffer::SetVertexCount(size_t count)
{
    _required_vertex_count = count;
}

size_t OgreVertexBuffer::GetVertexCount() const
{
    return _required_vertex_count;
}

TileShell::Drawing::Vertex* OgreVertexBuffer::Map()
{
    if (_required_vertex_count > _vertex_count)
    {
        ResizeVertexBuffer();
    }

    return reinterpret_cast<TileShell::Drawing::Vertex*>(_vertex_buffer->lock(
                Ogre::HardwareVertexBuffer::HBL_DISCARD));
}

void OgreVertexBuffer::Unmap()
{
    _vertex_buffer->unlock();
}

}


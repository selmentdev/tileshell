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
#ifndef _TileShell_Drawing_GeometryBuffer_H__
#define _TileShell_Drawing_GeometryBuffer_H__
//------------------------------------------------------------------------------------------------//
#include <tileshell.core/types.hxx>
#include <tileshell.core/reference.hxx>
#include <tileshell.core/referenced.hxx>
#include <tileshell.drawing/geometry.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{


///
/// This class represents geometry buffer resource.
///
class GeometryBuffer : public Core::Referenced
{
public:
    ///
    /// Destroys instance of the GeometryBuffer class.
    ///
    virtual ~GeometryBuffer() {}

public:
    ///
    /// Sets number of vertices in geometry buffer.
    ///
    virtual void SetVertexCount(size_t count) = 0;

    ///
    /// Gets number of vertices in geometry buffer.
    ///
    virtual size_t GetVertexCount() const = 0;

    ///
    /// Maps buffer in system memory.
    ///
    /// @returns
    ///     The pointer to mapped buffer.
    ///
    virtual Vertex* Map() = 0;

    ///
    /// Unmaps mapped buffer from system memory.
    ///
    virtual void Unmap() = 0;
};
typedef Core::Reference<GeometryBuffer> GeometryBufferRef;

}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Drawing_GeometryBuffer_H__ */
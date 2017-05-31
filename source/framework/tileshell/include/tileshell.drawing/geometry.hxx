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
#ifndef _TileShell_Drawing_Geometry_H__
#define _TileShell_Drawing_Geometry_H__
//------------------------------------------------------------------------------------------------//
#include <tileshell.core/types.hxx>
#include <tileshell.core/reference.hxx>
#include <tileshell.core/referenced.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
///
/// Vertex structure.
///
struct Vertex
{
    ///
    /// Vertex position in 3D space.
    ///
    float32x3_t Position;

    ///
    /// Texture color in vertex.
    ///
    uint32_t    Color;

    ///
    /// Texture coordinate in vertex.
    ///
    float32x2_t TexCoord;
};
typedef std::vector<Vertex, Core::StlAllocator<Vertex>> VertexArray;

enum PrimitiveType
{
    PrimitiveType_LineList,
    PrimitiveType_LineStrip,
    PrimitiveType_TriangleList,
    PrimitiveType_TriangleStrip,
};

class Geometry
{
private:
    VertexArray     _vertex_array;
    PrimitiveType   _primitive_type;

public:
    Geometry();
    ~Geometry();

    void Resize(size_t size);
    void Clear();

    Vertex& operator [] (size_t index);
    const Vertex& operator [] (size_t index) const;

    void Append(const Vertex& value);

    PrimitiveType GetPrimitiveType() const;
    void SetPrimitiveType(PrimitiveType value);

    Vertex* GetData();
    const Vertex* GetData() const;
};

}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Drawing_Geometry_H__ */
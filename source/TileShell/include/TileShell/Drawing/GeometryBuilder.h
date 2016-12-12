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
#ifndef _TileShell_Drawing_GeometryBuilder_H__
#define _TileShell_Drawing_GeometryBuilder_H__
//------------------------------------------------------------------------------------------------//
#include <TileShell/Core/Types.h>
#include <TileShell/Drawing/GeometryBuffer.h>
#include <TileShell/Drawing/Rect.h>
#include <TileShell/Drawing/Thickness.h>
#include <TileShell/Drawing/StyleItem.h>
#include <TileShell/Drawing/Matrix.h>
#include <TileShell/Drawing/Color.h>
#include <TileShell/Drawing/Font.h>
#include <TileShell/Drawing/StyleItem.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{

///
/// This class implements geometry buffer generation.
///
class GeometryBuilder
{
private:
    VertexArray         _vertex_collection;

public:
    ///
    /// Creates instance of the GeometryBuffer class.
    ///
    GeometryBuilder();

    ///
    /// Destroys instance of the GeometryBuffer class.
    ///
    virtual ~GeometryBuilder();

public:
    ///
    /// Begins geometry generation.
    ///
    void Begin();

    ///
    /// Ends geometry generation.
    ///
    /// @param[in,out] inout_geometry_buffer
    ///     A target geometry buffer.
    ///
    void End(GeometryBufferRef& inout_geometry_buffer);

    ///
    /// Adds quad.
    ///
    /// @param[in] v1
    ///     A first quad vertex.
    /// @param[in] v2
    ///     A second quad vertex.
    /// @param[in] v3
    ///     A third quad vertex.
    /// @param[in] v4
    ///     A fourth quad vertex.
    ///
    void AddQuad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4)
    {
        AddTriangle(v1, v2, v3);
        AddTriangle(v1, v3, v4);
    }

    ///
    /// Adds triangle.
    ///
    /// @param[in] v1
    ///     A first triangle vertex.
    /// @param[in] v2
    ///     A second triangle vertex.
    /// @param[in] v3
    ///     A third triangle vertex.
    ///
    void AddTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
    {
        _vertex_collection.push_back(v1);
        _vertex_collection.push_back(v2);
        _vertex_collection.push_back(v3);
    }

    ///
    /// Gets number of vertices in geometry builder.
    ///
    size_t GetVertexCount() const
    {
        return _vertex_collection.size();
    }

    ///
    /// Draws style item.
    ///
    /// @param[in] matrix
    ///     A transform matrix.
    /// @param[in] color
    ///     A color.
    /// @param[in] zindex
    ///     A Z index value.
    /// @param[in] rectangle
    ///     A rectangle to draw.
    /// @param[in] padding
    ///     An internal element padding.
    /// @param[in] style_item
    ///     A style item to draw.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool DrawStyleItem(
        const Matrix& matrix,
        const Color& color,
        float32_t zindex,
        const Rect& rectangle,
        const Thickness& padding,
        const StyleItem9Grid& style_item);

    ///
    /// Draws style item.
    ///
    /// @param[in] matrix
    ///     A transform matrix.
    /// @param[in] color
    ///     A color.
    /// @param[in] zindex
    ///     A Z index value.
    /// @param[in] rectangle
    ///     A rectangle to draw.
    /// @param[in] style_item
    ///     A style item to draw.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool DrawStyleItem(
        const Matrix& matrix,
        const Color& color,
        float32_t zindex,
        const Rect& rectangle,
        const StyleItem1Quad& style_item);

    ///
    /// Draws string.
    ///
    /// @param[in] matrix
    ///     A transform matrix.
    /// @param[in] color
    ///     A color.
    /// @param[in] zindex
    ///     A Z index value.
    /// @param[in] rectangle
    ///     A bound rectangle.
    /// @param[in] font
    ///     A font used to draw text.
    /// @param[in] font_size
    ///     A size of text to draw.
    /// @param[in] align
    ///     An alignment of text inside rectangle bound.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    bool DrawString(
        const Matrix& matrix,
        const Color& color,
        float32_t zindex,
        const Rect& rectangle,
        const FontRef& font,
        const char* text,
        float32_t font_size,
        TextAlign align = TextAlign_Center);
};

}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Drawing_GeometryBuilder_H__ */
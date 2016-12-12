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
#include <TileShell/Drawing/GeometryBuilder.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
//------------------------------------------------------------------------------------------------//
GeometryBuilder::GeometryBuilder()
    : _vertex_collection()
{
}
//------------------------------------------------------------------------------------------------//
GeometryBuilder::~GeometryBuilder()
{
}
//------------------------------------------------------------------------------------------------//
void GeometryBuilder::Begin()
{
    _vertex_collection.clear();
}
//------------------------------------------------------------------------------------------------//
void GeometryBuilder::End(GeometryBufferRef& inout_geometry_buffer)
{
    assert(inout_geometry_buffer.IsValid() == true);

    inout_geometry_buffer->SetVertexCount(_vertex_collection.size());

    Vertex* vertex = inout_geometry_buffer->Map();
    {
        for (VertexArray::const_iterator it = _vertex_collection.begin();
             it != _vertex_collection.end();
             ++it, ++vertex)
        {
            (*vertex) = (*it);
        }

    }
    inout_geometry_buffer->Unmap();
}
//------------------------------------------------------------------------------------------------//
bool GeometryBuilder::DrawStyleItem(
    const Matrix& matrix,
    const Color& color,
    float32_t zindex,
    const Rect& rectangle,
    const Thickness& padding,
    const StyleItem9Grid& style_item)
{
    float32x3_t points[16];
    float32x2_t texcoords[16];

    points[4 * 0 + 0] = float32x3_t(
                            rectangle.GetLeft(),
                            rectangle.GetTop(),
                            zindex);
    points[4 * 0 + 1] = float32x3_t(
                            rectangle.GetLeft() + padding.Left,
                            rectangle.GetTop(),
                            zindex);
    points[4 * 0 + 2] = float32x3_t(
                            rectangle.GetRight() - padding.Right,
                            rectangle.GetTop(),
                            zindex);
    points[4 * 0 + 3] = float32x3_t(
                            rectangle.GetRight(),
                            rectangle.GetTop(),
                            zindex);

    points[4 * 1 + 0] = float32x3_t(
                            rectangle.GetLeft(),
                            rectangle.GetTop() + padding.Top,
                            zindex);
    points[4 * 1 + 1] = float32x3_t(
                            rectangle.GetLeft() + padding.Left,
                            rectangle.GetTop() + padding.Top,
                            zindex);
    points[4 * 1 + 2] = float32x3_t(
                            rectangle.GetRight() - padding.Right,
                            rectangle.GetTop() + padding.Top,
                            zindex);
    points[4 * 1 + 3] = float32x3_t(
                            rectangle.GetRight(),
                            rectangle.GetTop() + padding.Top,
                            zindex);

    points[4 * 2 + 0] = float32x3_t(
                            rectangle.GetLeft(),
                            rectangle.GetBottom() - padding.Bottom,
                            zindex);
    points[4 * 2 + 1] = float32x3_t(
                            rectangle.GetLeft() + padding.Left,
                            rectangle.GetBottom() - padding.Bottom,
                            zindex);
    points[4 * 2 + 2] = float32x3_t(
                            rectangle.GetRight() - padding.Right,
                            rectangle.GetBottom() - padding.Bottom,
                            zindex);
    points[4 * 2 + 3] = float32x3_t(
                            rectangle.GetRight(),
                            rectangle.GetBottom() - padding.Bottom,
                            zindex);

    points[4 * 3 + 0] = float32x3_t(
                            rectangle.GetLeft(),
                            rectangle.GetBottom(),
                            zindex);
    points[4 * 3 + 1] = float32x3_t(
                            rectangle.GetLeft() + padding.Left,
                            rectangle.GetBottom(),
                            zindex);
    points[4 * 3 + 2] = float32x3_t(
                            rectangle.GetRight() - padding.Right,
                            rectangle.GetBottom(),
                            zindex);
    points[4 * 3 + 3] = float32x3_t(
                            rectangle.GetRight(),
                            rectangle.GetBottom(),
                            zindex);

    texcoords[4 * 0 + 0] = float32x2_t(
                               style_item.Rectangle.GetLeft(),
                               style_item.Rectangle.GetTop());
    texcoords[4 * 0 + 1] = float32x2_t(
                               style_item.Rectangle.GetLeft() + style_item.Padding.Left,
                               style_item.Rectangle.GetTop());
    texcoords[4 * 0 + 2] = float32x2_t(
                               style_item.Rectangle.GetRight() - style_item.Padding.Right,
                               style_item.Rectangle.GetTop());
    texcoords[4 * 0 + 3] = float32x2_t(
                               style_item.Rectangle.GetRight(),
                               style_item.Rectangle.GetTop());

    texcoords[4 * 1 + 0] = float32x2_t(
                               style_item.Rectangle.GetLeft(),
                               style_item.Rectangle.GetTop() + style_item.Padding.Top);
    texcoords[4 * 1 + 1] = float32x2_t(
                               style_item.Rectangle.GetLeft() + style_item.Padding.Left,
                               style_item.Rectangle.GetTop() + style_item.Padding.Top);
    texcoords[4 * 1 + 2] = float32x2_t(
                               style_item.Rectangle.GetRight() - style_item.Padding.Right,
                               style_item.Rectangle.GetTop() + style_item.Padding.Top);
    texcoords[4 * 1 + 3] = float32x2_t(
                               style_item.Rectangle.GetRight(),
                               style_item.Rectangle.GetTop() + style_item.Padding.Top);

    texcoords[4 * 2 + 0] = float32x2_t(
                               style_item.Rectangle.GetLeft(),
                               style_item.Rectangle.GetBottom() - style_item.Padding.Bottom);
    texcoords[4 * 2 + 1] = float32x2_t(
                               style_item.Rectangle.GetLeft() + style_item.Padding.Left,
                               style_item.Rectangle.GetBottom() - style_item.Padding.Bottom);
    texcoords[4 * 2 + 2] = float32x2_t(
                               style_item.Rectangle.GetRight() - style_item.Padding.Right,
                               style_item.Rectangle.GetBottom() - style_item.Padding.Bottom);
    texcoords[4 * 2 + 3] = float32x2_t(
                               style_item.Rectangle.GetRight(),
                               style_item.Rectangle.GetBottom() - style_item.Padding.Bottom);

    texcoords[4 * 3 + 0] = float32x2_t(
                               style_item.Rectangle.GetLeft(),
                               style_item.Rectangle.GetBottom());
    texcoords[4 * 3 + 1] = float32x2_t(
                               style_item.Rectangle.GetLeft() + style_item.Padding.Left,
                               style_item.Rectangle.GetBottom());
    texcoords[4 * 3 + 2] = float32x2_t(
                               style_item.Rectangle.GetRight() - style_item.Padding.Right,
                               style_item.Rectangle.GetBottom());
    texcoords[4 * 3 + 3] = float32x2_t(
                               style_item.Rectangle.GetRight(),
                               style_item.Rectangle.GetBottom());

    matrix.TransformPoints(points, 16);

    Drawing::Vertex v[16];

    for (size_t i = 0; i < 16; ++i)
    {
        v[i].Position = points[i];
        v[i].Color = color.ToUInt32();
        v[i].TexCoord = texcoords[i];
    }


    AddQuad(v[ 0], v[ 4], v[ 5], v[ 1]);
    AddQuad(v[ 1], v[ 5], v[ 6], v[ 2]);
    AddQuad(v[ 2], v[ 6], v[ 7], v[ 3]);

    AddQuad(v[ 4], v[ 8], v[ 9], v[ 5]);
    AddQuad(v[ 5], v[ 9], v[10], v[ 6]);
    AddQuad(v[ 6], v[10], v[11], v[ 7]);

    AddQuad(v[ 8], v[12], v[13], v[ 9]);
    AddQuad(v[ 9], v[13], v[14], v[10]);
    AddQuad(v[10], v[14], v[15], v[11]);
    return true;
}
//------------------------------------------------------------------------------------------------//
bool GeometryBuilder::DrawStyleItem(
    const Matrix& matrix,
    const Color& color,
    float32_t zindex,
    const Rect& rectangle,
    const StyleItem1Quad& style_item)
{
    float32x3_t points[4];
    points[0] = rectangle.GetTopLeft().ToFloat32x3(zindex);
    points[1] = rectangle.GetBottomLeft().ToFloat32x3(zindex);
    points[2] = rectangle.GetBottomRight().ToFloat32x3(zindex);
    points[3] = rectangle.GetTopRight().ToFloat32x3(zindex);

    matrix.TransformPoints(points, 4);

    Drawing::Vertex v1, v2, v3, v4;
    v1.Position = points[0];
    v2.Position = points[1];
    v3.Position = points[2];
    v4.Position = points[3];

    v1.Color = v2.Color = v3.Color = v4.Color = color.ToUInt32();

    v1.TexCoord     = style_item.Rectangle.GetTopLeft().ToFloat32x2();
    v2.TexCoord     = style_item.Rectangle.GetBottomLeft().ToFloat32x2();
    v3.TexCoord     = style_item.Rectangle.GetBottomRight().ToFloat32x2();
    v4.TexCoord     = style_item.Rectangle.GetTopRight().ToFloat32x2();

    AddQuad(v1, v2, v3, v4);
    return true;
}
//------------------------------------------------------------------------------------------------//
bool GeometryBuilder::DrawString(
    const Matrix& matrix,
    const Color& color,
    float32_t zindex,
    const Rect& rectangle,
    const FontRef& font,
    const char* text,
    float32_t font_size,
    TextAlign align)
{
    if (text == nullptr)
    {
        return false;
    }

    zindex += 1.0F;

    Drawing::Size size = font->MeasureString(text, font_size);

    Drawing::Rect textrect;
    textrect.SetSize(size);

    switch (align)
    {
    case Drawing::TextAlign_Left:
        {
            textrect.SetLocation(rectangle.GetTopLeft());
            break;
        }

    case Drawing::TextAlign_Center:
        {
            textrect.X = rectangle.X + rectangle.Width * 0.5F - size.Width * 0.5F;
            textrect.Y = rectangle.Y;
            break;
        }

    case Drawing::TextAlign_Right:
        {
            textrect.X = rectangle.X + rectangle.Width - size.Width;
            textrect.Y = rectangle.Y;
            break;
        }
    }

    float32_t x = textrect.X;
    float32_t y = rectangle.Y + (rectangle.Height - size.Height) * 0.5F;

    Drawing::Size font_scale = font->GetScale();

    float32_t inv_scale_x = 1.0F / font_scale.Width;
    float32_t inv_scale_y = 1.0F / font_scale.Height;

    float32_t font_size_scale = font_size / font->GetLineHeight();

    uint32_t color_as_uint32 = color.ToUInt32();

    for (; *text != '\0'; ++text)
    {
        char character = *text;

        switch (character)
        {
        case '\r':
            {
                continue;
            }

        case '\n':
            {
                x = textrect.X;
                y += font->GetLineHeight();
                break;
            }

        default:
            {
                const Drawing::FontGlyph* glyph = font->GetGlyph(character);

                if (glyph == nullptr)
                {
                    // Fallback to unknown glyph
                    glyph = font->GetGlyph('?');
                }

                Drawing::Vertex v1, v2, v3, v4;
                {
                    Drawing::Rect texcoord = glyph->Rectangle;
                    texcoord.X          *= inv_scale_x;
                    texcoord.Y          *= inv_scale_y;
                    texcoord.Width      *= inv_scale_x;
                    texcoord.Height     *= inv_scale_y;

                    Drawing::Rect placement = glyph->Rectangle;
                    placement.X         = x + glyph->Offset.X * font_size_scale;
                    placement.Y         = y + glyph->Offset.Y * font_size_scale;
                    placement.Width     *= font_size_scale;
                    placement.Height    *= font_size_scale;

                    float32x3_t points[4];
                    points[0] = placement.GetTopLeft().ToFloat32x3(zindex);
                    points[1] = placement.GetTopRight().ToFloat32x3(zindex);
                    points[2] = placement.GetBottomLeft().ToFloat32x3(zindex);
                    points[3] = placement.GetBottomRight().ToFloat32x3(zindex);

                    matrix.TransformPoints(points, 4);

                    v1.Position = points[0];
                    v2.Position = points[1];
                    v3.Position = points[2];
                    v4.Position = points[3];

                    v1.Color = v2.Color = v3.Color = v4.Color = color_as_uint32;

                    v1.TexCoord = texcoord.GetTopLeft().ToFloat32x2();
                    v2.TexCoord = texcoord.GetTopRight().ToFloat32x2();
                    v3.TexCoord = texcoord.GetBottomLeft().ToFloat32x2();
                    v4.TexCoord = texcoord.GetBottomRight().ToFloat32x2();

                    AddQuad(v1, v3, v4, v2);
                }

                x += /*glyph->Rectangle.Width + */glyph->Advance * font_size_scale;
                break;
            }
        }
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
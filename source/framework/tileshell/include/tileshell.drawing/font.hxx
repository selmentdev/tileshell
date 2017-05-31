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
#ifndef _TileShell_Drawing_Font_H__
#define _TileShell_Drawing_Font_H__
//------------------------------------------------------------------------------------------------//
#include <tileshell.core/reference.hxx>
#include <tileshell.core/referenced.hxx>
#include <tileshell.drawing/texture.hxx>
#include <tileshell.drawing/rect.hxx>
#include <tileshell.drawing/point.hxx>
#include <tileshell.drawing/size.hxx>
#include <tileshell.drawing/transform.hxx>
#include <tileshell.serialization/typeserializer.hxx>
#include <tileshell.xml/xml.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
class GeometryBuilder;

///
/// Specifies text alignment.
///
enum TextAlign
{
    TextAlign_Left,
    TextAlign_Center,
    TextAlign_Right,
};

///
/// Represents font glyph.
///
struct FontGlyph
{
    ///
    /// Font rectangle, in points.
    ///
    Rect            Rectangle;

    ///
    /// Additional offset.
    ///
    Point           Offset;

    ///
    /// Cursor advance value.
    ///
    float32_t       Advance;

    ///
    /// UTF16 code point.
    ///
    uint16_t        CodePoint;
};
typedef std::vector<FontGlyph, Core::StlAllocator<FontGlyph>>  FontGlyphCollection;

__forceinline bool operator < (const FontGlyph& left, const FontGlyph& right)
{
    return left.CodePoint < right.CodePoint;
}

__forceinline bool operator < (const FontGlyph& left, uint16_t code_point)
{
    return left.CodePoint < code_point;
}

__forceinline bool operator < (uint16_t code_point, const FontGlyph& right)
{
    return code_point < right.CodePoint;
}

///
/// Font kerning pair.
///
struct FontKerning
{
    ///
    /// First UTF16 code point.
    ///
    uint16_t        CodePoint1;

    ///
    /// Second UTF16 code point.
    ///
    uint16_t        CodePoint2;

    ///
    /// The kerning value.
    ///
    float32_t       Amount;
};
typedef std::vector<FontKerning, Core::StlAllocator<FontKerning>> FontKerningCollection;

///
/// Font object.
///
/// @remarks
///     This class provides interface to measuring and rendering text to geometry builder. It
///     represents specific font deserialized from XML file along with texture needed to render
///     it.
///
class Font
    : public Core::Referenced
    , public Core::Allocator<Font>
{
    friend class FontManager;

private:
    FontGlyphCollection     _font_glyph_collection;
    FontKerningCollection   _font_kerning_collection;
    string_t                _font_face;
    TextureRef              _font_texture;
    float32_t               _font_line_height;
    Size                    _font_scale;
    bool                    _is_bold;
    bool                    _is_italic;
    bool                    _is_smooth;
    bool                    _is_outline;

private:
    ///
    /// Creates instance of the Font class.
    ///
    Font();

    ///
    /// Destroys instance of the Font class.
    ///
    virtual ~Font();

public:
    ///
    /// Gets collection of font glyphs.
    ///
    const FontGlyphCollection& GetFontGlyphCollection() const
    {
        return _font_glyph_collection;
    }

    ///
    /// Gets collection of the font kerning pairs.
    ///
    const FontKerningCollection& GetFontKerningCollection() const
    {
        return _font_kerning_collection;
    }

    const string_t& GetFontFace() const
    {
        return _font_face;
    }

    ///
    /// Gets texture used to render text.
    ///
    const TextureRef& GetTexture() const
    {
        return _font_texture;
    }

    ///
    /// Sets texture used to render text.
    ///
    void SetTexture(const TextureRef& texture)
    {
        _font_texture = texture;
    }

    ///
    /// Gets height of text line.
    ///
    float32_t GetLineHeight() const
    {
        return _font_line_height;
    }

    ///
    /// Gets font scale.
    ///
    Size GetScale() const
    {
        return _font_scale;
    }

    ///
    /// Determines whether font is bold.
    ///
    bool IsBold() const
    {
        return _is_bold;
    }

    ///
    /// Determines whether font is italic.
    ///
    bool IsItalic() const
    {
        return _is_italic;
    }

    ///
    /// Determines whether font is smooth.
    ///
    bool IsSmooth() const
    {
        return _is_smooth;
    }

    ///
    /// Determines whether font has outline.
    ///
    bool IsOutline() const
    {
        return _is_outline;
    }

public:
    ///
    /// Gets glyph for specified code point.
    ///
    /// @param[out] out_result
    ///     A result font glyph data.
    /// @param[in] code_point
    ///     An UTF16 code point.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    /// @deprecated
    ///     This method generates unnecessary memory copying.
    ///
    bool GetGlyph(FontGlyph& out_result, uint16_t code_point) const;

    ///
    /// Gets glyph for specified code point.
    ///
    /// @param[in] code_point
    ///     An UTF16 code point.
    ///
    /// @returns
    ///     The pointer to glyph, nullptr when glyph not found.
    ///
    const FontGlyph* GetGlyph(uint16_t code_point) const;

    ///
    /// Gets kerning data for specified code point pair.
    ///
    /// @param[out] out_result
    ///     A result font kerning data.
    /// @param[in] code_point1
    ///     A source UTF16 code point.
    /// @param[in] code_point2
    ///     A source UTF16 code point.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    /// @deprecated
    ///     This method generates unnecessary memory copying.
    ///
    bool GetKerning(FontKerning& out_result, uint16_t code_point1, uint16_t code_point2) const;

    ///
    /// Gets kerning value for specified code point pair.
    ///
    /// @param[in] code_point1
    ///     A source UTF16 code point.
    /// @param[in] code_point2
    ///     A source UTF16 code point.
    ///
    /// @returns
    ///     The kerning value, 0.0 when kerning pair was not found.
    ///
    float32_t GetKerning(uint16_t code_point1, uint16_t code_point2) const;

public:
    ///
    /// Draws string from point (0, 0).
    ///
    /// @param[in,out] builder
    ///     A target geometry builder.
    /// @param[in] text
    ///     A text to draw.
    /// @param[in] color
    ///     A text color.
    /// @param[in] transform
    ///     A 2D transform.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool DrawString(GeometryBuilder& builder, const char* text, float32x4_t color,
                    const Transform& transform)
    {
        return DrawString(builder, text, ScaleToColor(color), transform);
    }

    ///
    /// Draws string from point (0, 0).
    ///
    /// @param[in,out] builder
    ///     A target geometry builder.
    /// @param[in] text
    ///     A text to draw.
    /// @param[in] color
    ///     A text color.
    /// @param[in] transform
    ///     A 2D transform.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool DrawString(GeometryBuilder& builder, const char* text, uint8x4_t color,
                    const Transform& transform);

    ///
    /// Draws string in provided rectangle.
    ///
    /// @param[in,out] builder
    ///     A target geometry builder.
    /// @param[in] text
    ///     A text to draw.
    /// @param[in] color
    ///     A text color.
    /// @param[in] rect
    ///     A rectangle in which text is rendered.
    /// @param[in] transform
    ///     A 2D transform.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool DrawString(GeometryBuilder& builder, const char* text, float32x4_t color, const Rect& rect,
                    const Transform& transform)
    {
        return DrawString(builder, text, ScaleToColor(color), rect, transform);
    }

    ///
    /// Draws string in provided rectangle.
    ///
    /// @param[in,out] builder
    ///     A target geometry builder.
    /// @param[in] text
    ///     A text to draw.
    /// @param[in] color
    ///     A text color.
    /// @param[in] rect
    ///     A rectangle in which text is rendered.
    /// @param[in] transform
    ///     A 2D transform.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool DrawString(GeometryBuilder& builder, const char* text, uint8x4_t color, const Rect& rect,
                    const Transform& transform);

    bool DrawStringFinal(GeometryBuilder& builder, const char* text, uint8x4_t color,
                         const Transform& transform)
    {
        Rect measured = Rect::CreateZeroRelative(MeasureString(text, _font_line_height));
        return DrawString(builder, text, color, measured, transform);
    }

    ///
    /// Gets text rectangle.
    ///
    /// @remarks
    ///     This method computes rectangle in which text is contained.
    ///
    /// @param[in] text
    ///     A text to measure.
    ///
    /// @returns
    ///     The rectangle containing text.
    ///
    Size MeasureString(const char* text, float32_t font_size);

private:
    bool Deserialize(Xml::XmlNode* node);
    bool Load(const string_t& path);
};
typedef Core::Reference<Font> FontRef;
//------------------------------------------------------------------------------------------------//
}
//------------------------------------------------------------------------------------------------//
namespace Serialization
{

template<>
struct ValueSerializer<Drawing::TextAlign>
{
    static bool Deserialize(Drawing::TextAlign& out_result, const Xml::XmlAttribute* attr)
    {
        if (attr == nullptr)
        {
            return false;
        }

        if (_stricmp(attr->value(), "Left") == 0)
        {
            out_result = Drawing::TextAlign_Left;
            return true;
        }
        else if (_stricmp(attr->value(), "Center") == 0)
        {
            out_result = Drawing::TextAlign_Center;

            return true;
        }
        else if (_stricmp(attr->value(), "Right") == 0)
        {
            out_result = Drawing::TextAlign_Right;

            return true;
        }

        return false;
    }
};

}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Drawing_Font_H__ */
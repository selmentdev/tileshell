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
#include <TileShell/Drawing/FontManager.h>
#include <TileShell/Drawing/Font.h>
#include <TileShell/Drawing/GeometryBuilder.h>
#include <TileShell/Drawing/TextureManager.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
//------------------------------------------------------------------------------------------------//
Font::Font()
    : _font_glyph_collection()
    , _font_kerning_collection()
    , _font_face()
    , _font_texture()
    , _font_line_height(1.0F)
    , _font_scale(1.0F, 1.0F)
    , _is_bold(false)
    , _is_italic(false)
    , _is_smooth(false)
    , _is_outline(false)
{
}
//------------------------------------------------------------------------------------------------//
Font::~Font()
{
}
//------------------------------------------------------------------------------------------------//
bool Font::GetGlyph(FontGlyph& out_result, uint16_t code_point) const
{
    FontGlyphCollection::const_iterator it = std::lower_bound(_font_glyph_collection.begin(),
            _font_glyph_collection.end(), code_point);

    if (it != _font_glyph_collection.end())
    {
        if (it->CodePoint == code_point)
        {
            out_result = (*it);
            return true;
        }
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
const FontGlyph* Font::GetGlyph(uint16_t code_point) const
{
    FontGlyphCollection::const_iterator it = std::lower_bound(_font_glyph_collection.begin(),
            _font_glyph_collection.end(), code_point);

    if (it != _font_glyph_collection.end())
    {
        if (it->CodePoint == code_point)
        {
            return &(*it);
        }
    }

    return nullptr;
}
//------------------------------------------------------------------------------------------------//
bool Font::GetKerning(FontKerning& out_result, uint16_t code_point1, uint16_t code_point2) const
{
    struct Pred
    {
        Pred(uint16_t code_point1, uint16_t code_point2)
            : _code_point1(code_point1)
            , _code_point2(code_point2)
        {
        }

        bool operator () (const FontKerning& kerning)
        {
            return (kerning.CodePoint1 == _code_point1) && (kerning.CodePoint2 == _code_point2);
        }

        uint16_t _code_point1;
        uint16_t _code_point2;
    };

    FontKerningCollection::const_iterator it = std::find_if(
                _font_kerning_collection.begin(),
                _font_kerning_collection.end(),
                Pred(code_point1, code_point2));

    if (it != _font_kerning_collection.end())
    {
        out_result = (*it);

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
float32_t Font::GetKerning(uint16_t code_point1, uint16_t code_point2) const
{
    struct Pred
    {
        Pred(uint16_t code_point1, uint16_t code_point2)
            : _code_point1(code_point1)
            , _code_point2(code_point2)
        {
        }

        bool operator () (const FontKerning& kerning)
        {
            return (kerning.CodePoint1 == _code_point1) && (kerning.CodePoint2 == _code_point2);
        }

        uint16_t _code_point1;
        uint16_t _code_point2;
    };

    FontKerningCollection::const_iterator it = std::find_if(
                _font_kerning_collection.begin(),
                _font_kerning_collection.end(),
                Pred(code_point1, code_point2));

    if (it != _font_kerning_collection.end())
    {
        return it->Amount;
    }

    return 0.0F;
}
//------------------------------------------------------------------------------------------------//
bool Font::DrawString(GeometryBuilder& builder, const char* text, uint8x4_t color,
                      const Transform& transform)
{
    return DrawString(builder, text, color, Rect(0.0F, 0.0F, 0.0F, 0.0F), transform);
}
//------------------------------------------------------------------------------------------------//
bool Font::DrawString(GeometryBuilder& builder, const char* text, uint8x4_t color, const Rect& rect,
                      const Transform& transform)
{
    tileshell_unused(transform);
    tileshell_unused(color);

    if (text == nullptr)
    {
        return false;
    }

    float32_t x = rect.X;
    float32_t y = rect.Y;

    float32_t inv_scale_x = 1.0F / _font_scale.Width;
    float32_t inv_scale_y = 1.0F / _font_scale.Height;

    //uint32_t color_as_uint32 = color.Value;

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
                x = rect.X;
                y += _font_line_height;
                break;
            }

        default:
            {
                const FontGlyph* glyph = GetGlyph(character);

                if (glyph == nullptr)
                {
                    // Fallback to unknown glyph
                    glyph = GetGlyph('?');
                }

                Drawing::Vertex v1, v2, v3, v4;
                {
                    Drawing::Rect texcoord = glyph->Rectangle;
                    texcoord.X          *= inv_scale_x;
                    texcoord.Y          *= inv_scale_y;
                    texcoord.Width      *= inv_scale_x;
                    texcoord.Height     *= inv_scale_y;

                    Drawing::Rect placement = glyph->Rectangle;
                    placement.X         = x + glyph->Offset.X;
                    placement.Y         = y + glyph->Offset.Y;
#if 0
#define dOGRE_WORKAROUND
#if defined(OGRE_WORKAROUND)

                    transform.TryTransform(v1.Position, placement.GetTopLeft().ToFloat32x2());
                    v1.TexCoord         = texcoord.GetBottomLeft().ToFloat32x2();
                    v1.Color            = color_as_uint32;

                    transform.TryTransform(v2.Position, placement.GetTopRight().ToFloat32x2());
                    v2.TexCoord         = texcoord.GetBottomRight().ToFloat32x2();
                    v2.Color            = color_as_uint32;

                    transform.TryTransform(v3.Position, placement.GetBottomLeft().ToFloat32x2());
                    v3.TexCoord         = texcoord.GetTopLeft().ToFloat32x2();
                    v3.Color            = color_as_uint32;

                    transform.TryTransform(v4.Position, placement.GetBottomRight().ToFloat32x2());
                    v4.TexCoord         = texcoord.GetTopRight().ToFloat32x2();
                    v4.Color            = color_as_uint32;

#else

#define ENABLE_TRANSFORM
#ifdef ENABLE_TRANSFORM
                    transform.TryTransform(v1.Position, placement.GetTopLeft().ToFloat32x2());
#else
                    v1.Position         = float32x3_t(placement.GetTopLeft(), 0.0F);
#endif
                    v1.TexCoord         = texcoord.GetTopLeft().ToFloat32x2();
                    v1.Color            = color_as_uint32;

#ifdef ENABLE_TRANSFORM
                    transform.TryTransform(v2.Position, placement.GetTopRight().ToFloat32x2());
#else
                    v2.Position         = float32x3_t(placement.GetTopRight(), 0.0F);
#endif
                    v2.TexCoord         = texcoord.GetTopRight().ToFloat32x2();
                    v2.Color            = color_as_uint32;

#ifdef ENABLE_TRANSFORM
                    transform.TryTransform(v3.Position, placement.GetBottomLeft().ToFloat32x2());
#else
                    v3.Position         = float32x3_t(placement.GetBottomLeft(), 0.0F);
#endif
                    v3.TexCoord         = texcoord.GetBottomLeft().ToFloat32x2();
                    v3.Color            = color_as_uint32;

#ifdef ENABLE_TRANSFORM
                    transform.TryTransform(v4.Position, placement.GetBottomRight().ToFloat32x2());
#else
                    v4.Position         = float32x3_t(placement.GetBottomRight(), 0.0F);
#endif
                    v4.TexCoord         = texcoord.GetBottomRight().ToFloat32x2();
                    v4.Color            = color_as_uint32;
#endif
#endif

                    builder.AddQuad(v1, v3, v4, v2);
                }

                x += /*glyph->Rectangle.Width + */glyph->Advance;
                break;
            }
        }
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
Size Font::MeasureString(const char* text, float32_t font_size)
{
    if (text != nullptr)
    {
        float32_t x = 0.0F;
        float32_t y = 0.0F;

        float32_t width = 0.0F;
        float32_t height = 0.0F;

        float32_t font_size_scale = font_size / _font_line_height;

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
                    x = 0.0F;
                    y += font_size;
                    break;
                }

            default:
                {
                    const FontGlyph* glyph = GetGlyph(character);

                    if (glyph == nullptr)
                    {
                        // Fallback to unknown glyph
                        glyph = GetGlyph('?');
                    }

                    float32_t w = glyph->Rectangle.Width * font_size_scale;
                    float32_t h = (glyph->Rectangle.Height + glyph->Offset.Y) * font_size_scale;

                    h = std::max(h, _font_line_height * font_size_scale);

                    width = std::max(width, x + w);
                    height = std::max(height, y + h);

                    x += glyph->Advance * font_size_scale;
                    break;
                }
            }
        }

        return Size(width, height);
    }

    return Size();
}
//------------------------------------------------------------------------------------------------//
bool Font::Deserialize(Xml::XmlNode* node)
{
    using namespace Serialization;

    Xml::XmlNode* common        = node->first_node("common");
    Xml::XmlNode* pages         = node->first_node("pages");
    Xml::XmlNode* chars         = node->first_node("chars");
    Xml::XmlNode* kernings      = node->first_node("kernings");
    Xml::XmlNode* info          = node->first_node("info");

    if (common == nullptr || pages == nullptr || chars == nullptr)
    {
        return false;
    }

    if (info != nullptr)
    {
        StringValueSerializer::Deserialize(_font_face,  info->first_attribute("face"));
        BoolValueSerializer::Deserialize(_is_bold,      info->first_attribute("bold"));
        BoolValueSerializer::Deserialize(_is_italic,    info->first_attribute("italic"));
        BoolValueSerializer::Deserialize(_is_smooth,    info->first_attribute("smooth"));
        BoolValueSerializer::Deserialize(_is_outline,   info->first_attribute("outline"));
    }

    FloatValueSerializer::Deserialize(_font_line_height,   common->first_attribute("lineHeight"));
    FloatValueSerializer::Deserialize(_font_scale.Width,   common->first_attribute("scaleW"));
    FloatValueSerializer::Deserialize(_font_scale.Height,  common->first_attribute("scaleH"));

    if (Xml::XmlNode* page = pages->first_node("page"))
    {
        if (Xml::XmlAttribute* file = page->first_attribute("file"))
        {
            _font_texture = TextureManager::GetTexture(file->value());
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    for (Xml::XmlNode* character = chars->first_node("char");
         character != nullptr;
         character = character->next_sibling("char"))
    {
        FontGlyph glyph;
        UInt16ValueSerializer::Deserialize(glyph.CodePoint,         character->first_attribute("id"));
        FloatValueSerializer::Deserialize(glyph.Rectangle.X,        character->first_attribute("x"));
        FloatValueSerializer::Deserialize(glyph.Rectangle.Y,        character->first_attribute("y"));
        FloatValueSerializer::Deserialize(glyph.Rectangle.Width,    character->first_attribute("width"));
        FloatValueSerializer::Deserialize(glyph.Rectangle.Height,   character->first_attribute("height"));
        FloatValueSerializer::Deserialize(glyph.Offset.X,           character->first_attribute("xoffset"));
        FloatValueSerializer::Deserialize(glyph.Offset.Y,           character->first_attribute("yoffset"));
        FloatValueSerializer::Deserialize(glyph.Advance,            character->first_attribute("xadvance"));

        _font_glyph_collection.push_back(glyph);
    }

    std::sort(_font_glyph_collection.begin(), _font_glyph_collection.end());

    if (kernings != nullptr)
    {
        for (Xml::XmlNode* kerning = kernings->first_node("kerning");
             kerning != nullptr;
             kerning = kerning->next_sibling("kerning"))
        {
            FontKerning font_kerning;
            UInt16ValueSerializer::Deserialize(font_kerning.CodePoint1, kerning->first_attribute("first"));
            UInt16ValueSerializer::Deserialize(font_kerning.CodePoint2, kerning->first_attribute("second"));
            FloatValueSerializer::Deserialize(font_kerning.Amount,      kerning->first_attribute("amount"));

            _font_kerning_collection.push_back(font_kerning);
        }
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool Font::Load(const string_t& name)
{
    Xml::XmlFile file(name.c_str());
    Xml::XmlDocument doc;
    doc.parse<0>(file.data());

    return Deserialize(doc.first_node("font"));
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
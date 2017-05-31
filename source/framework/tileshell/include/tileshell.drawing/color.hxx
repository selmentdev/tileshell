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
#ifndef _TileShell_Drawing_Color_H__
#define _TileShell_Drawing_Color_H__
//------------------------------------------------------------------------------------------------//
#include <tileshell/required.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
///
/// List of known colors.
///
enum ColorKnown
{
    ColorKnown_AntiqueWhite            = 0xFFFAEBD7,
    ColorKnown_Aqua                    = 0xFF00FFFF,
    ColorKnown_Aquamarine              = 0xFF7FFFD4,
    ColorKnown_Azure                   = 0xFFF0FFFF,
    ColorKnown_Beige                   = 0xFFF5F5DC,
    ColorKnown_Bisque                  = 0xFFFFE4C4,
    ColorKnown_Black                   = 0xFF000000,
    ColorKnown_BlanchedAlmond          = 0xFFFFEBCD,
    ColorKnown_Blue                    = 0xFF0000FF,
    ColorKnown_BlueViolet              = 0xFF8A2BE2,
    ColorKnown_Brown                   = 0xFFA52A2A,
    ColorKnown_BurlyWood               = 0xFFDEB887,
    ColorKnown_CadetBlue               = 0xFF5F9EA0,
    ColorKnown_Chartreuse              = 0xFF7FFF00,
    ColorKnown_Chocolate               = 0xFFD2691E,
    ColorKnown_Coral                   = 0xFFFF7F50,
    ColorKnown_CornflowerBlue          = 0xFF6495ED,
    ColorKnown_Cornsilk                = 0xFFFFF8DC,
    ColorKnown_Crimson                 = 0xFFDC143C,
    ColorKnown_Cyan                    = 0xFF00FFFF,
    ColorKnown_DarkBlue                = 0xFF00008B,
    ColorKnown_DarkCyan                = 0xFF008B8B,
    ColorKnown_DarkGoldenrod           = 0xFFB8860B,
    ColorKnown_DarkGray                = 0xFFA9A9A9,
    ColorKnown_DarkGreen               = 0xFF006400,
    ColorKnown_DarkKhaki               = 0xFFBDB76B,
    ColorKnown_DarkMagenta             = 0xFF8B008B,
    ColorKnown_DarkOliveGreen          = 0xFF556B2F,
    ColorKnown_DarkOrange              = 0xFFFF8C00,
    ColorKnown_DarkOrchid              = 0xFF9932CC,
    ColorKnown_DarkRed                 = 0xFF8B0000,
    ColorKnown_DarkSalmon              = 0xFFE9967A,
    ColorKnown_DarkSeaGreen            = 0xFF8FBC8F,
    ColorKnown_DarkSlateBlue           = 0xFF483D8B,
    ColorKnown_DarkSlateGray           = 0xFF2F4F4F,
    ColorKnown_DarkTurquoise           = 0xFF00CED1,
    ColorKnown_DarkViolet              = 0xFF9400D3,
    ColorKnown_DeepPink                = 0xFFFF1493,
    ColorKnown_DeepSkyBlue             = 0xFF00BFFF,
    ColorKnown_DimGray                 = 0xFF696969,
    ColorKnown_DodgerBlue              = 0xFF1E90FF,
    ColorKnown_Firebrick               = 0xFFB22222,
    ColorKnown_FloralWhite             = 0xFFFFFAF0,
    ColorKnown_ForestGreen             = 0xFF228B22,
    ColorKnown_Fuchsia                 = 0xFFFF00FF,
    ColorKnown_Gainsboro               = 0xFFDCDCDC,
    ColorKnown_GhostWhite              = 0xFFF8F8FF,
    ColorKnown_Gold                    = 0xFFFFD700,
    ColorKnown_Goldenrod               = 0xFFDAA520,
    ColorKnown_Gray                    = 0xFF808080,
    ColorKnown_Green                   = 0xFF008000,
    ColorKnown_GreenYellow             = 0xFFADFF2F,
    ColorKnown_Honeydew                = 0xFFF0FFF0,
    ColorKnown_HotPink                 = 0xFFFF69B4,
    ColorKnown_IndianRed               = 0xFFCD5C5C,
    ColorKnown_Indigo                  = 0xFF4B0082,
    ColorKnown_Ivory                   = 0xFFFFFFF0,
    ColorKnown_Khaki                   = 0xFFF0E68C,
    ColorKnown_Lavender                = 0xFFE6E6FA,
    ColorKnown_LavenderBlush           = 0xFFFFF0F5,
    ColorKnown_LawnGreen               = 0xFF7CFC00,
    ColorKnown_LemonChiffon            = 0xFFFFFACD,
    ColorKnown_LightBlue               = 0xFFADD8E6,
    ColorKnown_LightCoral              = 0xFFF08080,
    ColorKnown_LightCyan               = 0xFFE0FFFF,
    ColorKnown_LightGoldenrodYellow    = 0xFFFAFAD2,
    ColorKnown_LightGray               = 0xFFD3D3D3,
    ColorKnown_LightGreen              = 0xFF90EE90,
    ColorKnown_LightPink               = 0xFFFFB6C1,
    ColorKnown_LightSalmon             = 0xFFFFA07A,
    ColorKnown_LightSeaGreen           = 0xFF20B2AA,
    ColorKnown_LightSkyBlue            = 0xFF87CEFA,
    ColorKnown_LightSlateGray          = 0xFF778899,
    ColorKnown_LightSteelBlue          = 0xFFB0C4DE,
    ColorKnown_LightYellow             = 0xFFFFFFE0,
    ColorKnown_Lime                    = 0xFF00FF00,
    ColorKnown_LimeGreen               = 0xFF32CD32,
    ColorKnown_Linen                   = 0xFFFAF0E6,
    ColorKnown_Magenta                 = 0xFFFF00FF,
    ColorKnown_Maroon                  = 0xFF800000,
    ColorKnown_MediumAquamarine        = 0xFF66CDAA,
    ColorKnown_MediumBlue              = 0xFF0000CD,
    ColorKnown_MediumOrchid            = 0xFFBA55D3,
    ColorKnown_MediumPurple            = 0xFF9370DB,
    ColorKnown_MediumSeaGreen          = 0xFF3CB371,
    ColorKnown_MediumSlateBlue         = 0xFF7B68EE,
    ColorKnown_MediumSpringGreen       = 0xFF00FA9A,
    ColorKnown_MediumTurquoise         = 0xFF48D1CC,
    ColorKnown_MediumVioletRed         = 0xFFC71585,
    ColorKnown_MidnightBlue            = 0xFF191970,
    ColorKnown_MintCream               = 0xFFF5FFFA,
    ColorKnown_MistyRose               = 0xFFFFE4E1,
    ColorKnown_Moccasin                = 0xFFFFE4B5,
    ColorKnown_NavajoWhite             = 0xFFFFDEAD,
    ColorKnown_Navy                    = 0xFF000080,
    ColorKnown_OldLace                 = 0xFFFDF5E6,
    ColorKnown_Olive                   = 0xFF808000,
    ColorKnown_OliveDrab               = 0xFF6B8E23,
    ColorKnown_Orange                  = 0xFFFFA500,
    ColorKnown_OrangeRed               = 0xFFFF4500,
    ColorKnown_Orchid                  = 0xFFDA70D6,
    ColorKnown_PaleGoldenrod           = 0xFFEEE8AA,
    ColorKnown_PaleGreen               = 0xFF98FB98,
    ColorKnown_PaleTurquoise           = 0xFFAFEEEE,
    ColorKnown_PaleVioletRed           = 0xFFDB7093,
    ColorKnown_PapayaWhip              = 0xFFFFEFD5,
    ColorKnown_PeachPuff               = 0xFFFFDAB9,
    ColorKnown_Peru                    = 0xFFCD853F,
    ColorKnown_Pink                    = 0xFFFFC0CB,
    ColorKnown_Plum                    = 0xFFDDA0DD,
    ColorKnown_PowderBlue              = 0xFFB0E0E6,
    ColorKnown_Purple                  = 0xFF800080,
    ColorKnown_Red                     = 0xFFFF0000,
    ColorKnown_RosyBrown               = 0xFFBC8F8F,
    ColorKnown_RoyalBlue               = 0xFF4169E1,
    ColorKnown_SaddleBrown             = 0xFF8B4513,
    ColorKnown_Salmon                  = 0xFFFA8072,
    ColorKnown_SandyBrown              = 0xFFF4A460,
    ColorKnown_SeaGreen                = 0xFF2E8B57,
    ColorKnown_SeaShell                = 0xFFFFF5EE,
    ColorKnown_Sienna                  = 0xFFA0522D,
    ColorKnown_Silver                  = 0xFFC0C0C0,
    ColorKnown_SkyBlue                 = 0xFF87CEEB,
    ColorKnown_SlateBlue               = 0xFF6A5ACD,
    ColorKnown_SlateGray               = 0xFF708090,
    ColorKnown_Snow                    = 0xFFFFFAFA,
    ColorKnown_SpringGreen             = 0xFF00FF7F,
    ColorKnown_SteelBlue               = 0xFF4682B4,
    ColorKnown_Tan                     = 0xFFD2B48C,
    ColorKnown_Teal                    = 0xFF008080,
    ColorKnown_Thistle                 = 0xFFD8BFD8,
    ColorKnown_Tomato                  = 0xFFFF6347,
    ColorKnown_Turquoise               = 0xFF40E0D0,
    ColorKnown_Violet                  = 0xFFEE82EE,
    ColorKnown_Wheat                   = 0xFFF5DEB3,
    ColorKnown_White                   = 0xFFFFFFFF,
    ColorKnown_WhiteSmoke              = 0xFFF5F5F5,
    ColorKnown_Yellow                  = 0xFFFFFF00,
    ColorKnown_YellowGreen             = 0xFF9ACD32,
};

///
/// Represents an ARGB color.
///
struct Color
{
public:
    union
    {
        uint32_t    _argb;
        struct
        {
            uint8_t _b;
            uint8_t _g;
            uint8_t _r;
            uint8_t _a;
        };
    };

public:
    ///
    /// Creates instance of Color struct.
    ///
    Color();

    ///
    /// Creates instance of Color struct using color encoded as uint32_t value.
    ///
    /// @param[in] value
    ///     An encoded color value.
    ///
    Color(uint32_t value);

    ///
    /// Creates instance of Color struct using ColorKnown enumeration.
    ///
    Color(ColorKnown value);

    ///
    /// Creates instance of Color struct using red green and blue components separately.
    ///
    /// @param[in] r
    ///     A red component value.
    /// @param[in] g
    ///     A green component value.
    /// @param[in] b
    ///     A blue component value.
    Color(uint8_t r, uint8_t g, uint8_t b);

    ///
    /// Creates instance of Color struct using red green, blue and alpha components separately.
    ///
    /// @param[in] r
    ///     A red component value.
    /// @param[in] g
    ///     A green component value.
    /// @param[in] b
    ///     A blue component value.
    /// @param[in] a
    ///     An alpha component value.
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    ///
    /// Creates instance of Color struct using red green, blue and alpha components separately.
    ///
    /// @param[in] r
    ///     A red component value.
    /// @param[in] g
    ///     A green component value.
    /// @param[in] b
    ///     A blue component value.
    /// @param[in] a
    ///     An alpha component value.
    Color(float32_t r, float32_t g, float32_t b, float32_t a);

    ///
    /// Gets red component value.
    ///
    uint8_t GetR() const;

    ///
    /// Gets green component value.
    ///
    uint8_t GetG() const;

    ///
    /// Gets blue component value.
    ///
    uint8_t GetB() const;

    ///
    /// Gets alpha component value.
    ///
    uint8_t GetA() const;

    ///
    /// Converts color to vector of float32_t values.
    ///
    float32x4_t ToFloat32x4() const;

    ///
    /// Converts color to uint32_t value.
    ///
    uint32_t ToUInt32() const;
};
//------------------------------------------------------------------------------------------------//
inline Color::Color()
    : _argb(0)
{
}
//------------------------------------------------------------------------------------------------//
inline Color::Color(uint32_t value)
    : _argb(value)
{
}
//------------------------------------------------------------------------------------------------//
inline Color::Color(ColorKnown value)
    : _argb(value)
{
}
//------------------------------------------------------------------------------------------------//
inline Color::Color(uint8_t r, uint8_t g, uint8_t b)
    : _r(r)
    , _g(g)
    , _b(b)
    , _a(0xFF)
{
}
//------------------------------------------------------------------------------------------------//
inline Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : _r(r)
    , _g(g)
    , _b(b)
    , _a(a)
{
}
//------------------------------------------------------------------------------------------------//
inline Color::Color(float32_t r, float32_t g, float32_t b, float32_t a)
    : _r(static_cast<uint8_t>(r * 255.0F))
    , _g(static_cast<uint8_t>(g * 255.0F))
    , _b(static_cast<uint8_t>(b * 255.0F))
    , _a(static_cast<uint8_t>(a * 255.0F))
{
}
//------------------------------------------------------------------------------------------------//
inline uint8_t Color::GetR() const
{
    return _r;
}
//------------------------------------------------------------------------------------------------//
inline uint8_t Color::GetG() const
{
    return _g;
}
//------------------------------------------------------------------------------------------------//
inline uint8_t Color::GetB() const
{
    return _b;
}
//------------------------------------------------------------------------------------------------//
inline uint8_t Color::GetA() const
{
    return _a;
}
//------------------------------------------------------------------------------------------------//
inline float32x4_t Color::ToFloat32x4() const
{
    return float32x4_t(
               static_cast<float32_t>(_r) / 255.0F,
               static_cast<float32_t>(_g) / 255.0F,
               static_cast<float32_t>(_b) / 255.0F,
               static_cast<float32_t>(_a) / 255.0F);
}
//------------------------------------------------------------------------------------------------//
inline uint32_t Color::ToUInt32() const
{
    return _argb;
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Drawing_Color_H__ */
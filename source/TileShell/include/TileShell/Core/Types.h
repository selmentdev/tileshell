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
#ifndef _TileShell_Core_Types_H__
#define _TileShell_Core_Types_H__
//------------------------------------------------------------------------------------------------//
#include <TileShell/Required.h>
#include <TileShell/Core/Allocator.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Types
{
typedef std::basic_string<char, std::char_traits<char>, Core::StlAllocator<char>> string_t;

struct float32x2_t
{
    float32x2_t()
    {
    }

    explicit float32x2_t(float32_t value)
        : X(value)
        , Y(value)
    {
    }

    float32x2_t(float32_t x, float32_t y)
        : X(x)
        , Y(y)
    {
    }

    float32_t   X;
    float32_t   Y;
};

struct float32x3_t
{
    float32x3_t()
    {
    }

    explicit float32x3_t(float32_t value)
        : X(value)
        , Y(value)
        , Z(value)
    {
    }

    float32x3_t(float32x2_t xy, float32_t z)
        : X(xy.X)
        , Y(xy.Y)
        , Z(z)
    {
    }

    float32x3_t(float32_t x, float32_t y, float32_t z)
        : X(x)
        , Y(y)
        , Z(z)
    {
    }

    float32x3_t ToFloat32x3() const
    {
        return (*this);
    }

    float32x2_t ToFloat32x2() const
    {
        return float32x2_t(X, Y);
    }

    float32_t   X;
    float32_t   Y;
    float32_t   Z;
};

struct float32x4_t
{
    float32x4_t()
    {
    }

    explicit float32x4_t(float32_t value)
        : X(value)
        , Y(value)
        , Z(value)
        , W(value)
    {
    }

    float32x4_t(float32x2_t xy, float32_t z, float32_t w)
        : X(xy.X)
        , Y(xy.Y)
        , Z(z)
        , W(w)
    {
    }

    float32x4_t(float32x3_t xyz, float32_t w)
        : X(xyz.X)
        , Y(xyz.Y)
        , Z(xyz.Z)
        , W(w)
    {
    }

    float32x4_t(float32_t x, float32_t y, float32_t z, float32_t w)
        : X(x)
        , Y(y)
        , Z(z)
        , W(w)
    {
    }

    float32x4_t ToFloat32x4() const
    {
        return (*this);
    }

    float32x3_t ToFloat32x3() const
    {
        return float32x3_t(X, Y, Z);
    }

    float32x2_t ToFloat32x2() const
    {
        return float32x2_t(X, Y);
    }

    float32x3_t ToFloat32x3Homogenous() const
    {
        float32_t inv_w = 1.0F / W;

        return float32x3_t(X * inv_w, Y * inv_w, Z * inv_w);
    }

    float32_t   X;
    float32_t   Y;
    float32_t   Z;
    float32_t   W;
};

struct uint8x4_t
{
    union
    {
        uint32_t Value;

        struct
        {
            uint8_t R;
            uint8_t G;
            uint8_t B;
            uint8_t A;
        };
    };

    uint8x4_t()
    {
    }

    explicit uint8x4_t(uint32_t value)
    {
        Value = value;
    }

    uint8x4_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }
};

static inline uint8x4_t ScaleToColor(const float32x4_t& color)
{
    uint8_t x = static_cast<uint8_t>(color.X * 255.0F);
    uint8_t y = static_cast<uint8_t>(color.Y * 255.0F);
    uint8_t z = static_cast<uint8_t>(color.Z * 255.0F);
    uint8_t w = static_cast<uint8_t>(color.W * 255.0F);

    return uint8x4_t(x, y, z, w);
}

}

using namespace Types;
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Core_Types_H__ */
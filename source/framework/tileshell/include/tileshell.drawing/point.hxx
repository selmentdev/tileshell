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
#ifndef _TileShell_Drawing_Point_H__
#define _TileShell_Drawing_Point_H__

#include <tileshell.core/types.hxx>

namespace TileShell::Drawing
{

    ///
    /// Represents point in 2D space.
    ///
    struct Point
    {
    public:
        float32_t   X;
        float32_t   Y;

    public:
        ///
        /// Creates instance of the Point struct.
        ///
        Point();

        ///
        /// Creates instance of the Point struct using another point..
        ///
        /// @param[in] v
        ///     An instance of point to copy.
        ///
        Point(const Point& v);

        ///
        /// Creates instance of the Point struct.
        ///
        /// @param[in] value
        ///     A value to set point coordinates.
        ///
        Point(float32_t value);

        ///
        /// Creates instance of the Point struct.
        ///
        /// @param[in] x
        ///     An X point coordinate.
        /// @param[in] y
        ///     An Y point coordinate.
        ///
        Point(float32_t x, float32_t y);

    public:
        ///
        /// Converts point to float32x2_t type.
        ///
        float32x2_t ToFloat32x2() const;

        ///
        /// Converts point to float32x3_t type.
        ///
        /// @remarks
        ///     Sets Z coordinate to 0.0F
        float32x3_t ToFloat32x3() const;

        ///
        /// Converts point to float32x3_t type.
        ///
        /// @param[in] z
        ///     An Z point coordinate.
        ///
        float32x3_t ToFloat32x3(float32_t z) const;

    public:
        bool IsEmpty() const;
        bool operator == (const Point& p) const;
        bool operator != (const Point& p) const;
    };

    inline Point::Point()
        : X(0.0F)
        , Y(0.0F)
    {
    }

    inline Point::Point(const Point& v)
        : X(v.X)
        , Y(v.Y)
    {
    }

    inline Point::Point(float32_t value)
        : X(value)
        , Y(value)
    {
    }

    inline Point::Point(float32_t x, float32_t y)
        : X(x)
        , Y(y)
    {
    }

    inline float32x2_t Point::ToFloat32x2() const
    {
        return float32x2_t(X, Y);
    }

    inline float32x3_t Point::ToFloat32x3() const
    {
        return float32x3_t(X, Y, 0.0F);
    }

    inline float32x3_t Point::ToFloat32x3(float32_t z) const
    {
        return float32x3_t(X, Y, z);
    }

    inline bool Point::IsEmpty() const
    {
        return X == 0.0F && Y == 0.0F;
    }

    inline bool Point::operator == (const Point& p) const
    {
        return X == p.X && Y == p.Y;
    }

    inline bool Point::operator != (const Point& p) const
    {
        return X != p.X || Y != p.Y;
    }

}

#endif /* _TileShell_Drawing_Point_H__ */
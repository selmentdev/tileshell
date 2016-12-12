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

#include <TileShell/Drawing/Point.h>

namespace TileShell
{
namespace Drawing
{
///
/// @brief
///     This struct represents vector in 2D space.
///
struct Vector
{
    float32_t   X;
    float32_t   Y;

    Vector()
        : X(0.0F)
        , Y(0.0F)
    {
    }

    explicit Vector(float32_t value)
        : X(value)
        , Y(value)
    {
    }

    Vector(float32_t x, float32_t y)
        : X(x)
        , Y(y)
    {
    }

    explicit Vector(const Point& point)
        : X(point.X)
        , Y(point.Y)
    {
    }

};

///
/// @brief
///     This struct represents vector in 3D space.
///
struct Vector3
{
    float32_t   X;
    float32_t   Y;
    float32_t   Z;

    Vector3()
        : X(0.0F)
        , Y(0.0F)
        , Z(0.0F)
    {
    }

    explicit Vector3(float32_t value)
        : X(value)
        , Y(value)
        , Z(value)
    {
    }

    Vector3(float32_t x, float32_t y, float32_t z)
        : X(x)
        , Y(y)
        , Z(z)
    {
    }

    explicit Vector3(const Point& point)
        : X(point.X)
        , Y(point.Y)
        , Z(0.0F)
    {
    }

    Vector3(const Point& point, float32_t z)
        : X(point.X)
        , Y(point.Y)
        , Z(z)
    {
    }

};

}
}
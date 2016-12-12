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
#ifndef _TileShell_Drawing_Rectangle_H__
#define _TileShell_Drawing_Rectangle_H__
//------------------------------------------------------------------------------------------------//
#include <TileShell/Core/Types.h>
#include <TileShell/Drawing/Point.h>
#include <TileShell/Drawing/Size.h>
#include <TileShell/Drawing/Vector.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
struct Size;
struct Point;
struct Thickness;

///
/// This struct represents axis oriented rectangle in 2D space.
///
struct Rect
{
public:
    float32_t   X;
    float32_t   Y;
    float32_t   Width;
    float32_t   Height;

public:
    Rect();
    explicit Rect(float32_t value);
    Rect(float32_t x, float32_t y, float32_t size);
    Rect(float32_t x, float32_t y, float32_t width, float32_t height);
    explicit Rect(const Size& size);
    Rect(const Point& point, const Vector& vector);
    Rect(const Point& point1, const Point& point2);
    Rect(const Point& location, const Size& size);

public:
    bool operator == (const Rect& r) const;
    bool operator != (const Rect& r) const;

public:
    float32_t GetLeft() const;
    float32_t GetTop() const;
    float32_t GetWidth() const;
    float32_t GetHeight() const;
    float32_t GetRight() const;
    float32_t GetBottom() const;

    Point GetLocation() const;
    Rect& SetLocation(const Point& value);
    Size GetSize() const;
    Rect& SetSize(const Size& size);

    Point GetTopLeft() const;
    Point GetTopRight() const;
    Point GetBottomLeft() const;
    Point GetBottomRight() const;
    Point GetCenter() const;

    Rect& SetCenter(const Point& value);

public:
    static Rect CreateZeroRelative(float32_t width, float32_t height);
    static Rect CreateZeroRelative(const Size& size);

public:
    Rect& Scale(const Size& size);

    Rect& Inflate(float32_t left, float32_t top, float32_t right, float32_t bottom);
    Rect& Inflate(float32_t horizontal, float32_t vertical);
    Rect& Inflate(float32_t value);
    Rect& Inflate(const Size& size);
    Rect& Inflate(const Thickness& value);

    Rect& Deflate(float32_t left, float32_t top, float32_t right, float32_t bottom);
    Rect& Deflate(float32_t horizontal, float32_t vertical);
    Rect& Deflate(float32_t value);
    Rect& Deflate(const Size& size);
    Rect& Deflate(const Thickness& value);

    Rect& Offset(float32_t x, float32_t y);

    Rect& Offset(const Vector& offset);

    Rect& Intersect(const Rect& r);

    Rect& Union(const Rect& r);

    Rect& Union(const Point& p);

public:
    bool Contains(const Rect& r) const;

    bool Contains(float32_t x, float32_t y) const;

    bool Contains(const Point& point) const;

    bool IntersectsWith(const Rect& r) const;

    Point Clamp(const Point& p) const;
};
}
}
//------------------------------------------------------------------------------------------------//
#include <TileShell/Drawing/Rect.inl>
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Drawing_Rectangle_H__ */
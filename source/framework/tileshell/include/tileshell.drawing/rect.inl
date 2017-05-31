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
//------------------------------------------------------------------------------------------------//
#include <tileshell.drawing/size.hxx>
#include <tileshell.drawing/vector.hxx>
#include <tileshell.drawing/point.hxx>
#include <tileshell.drawing/rect.hxx>
#include <tileshell.drawing/thickness.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
//------------------------------------------------------------------------------------------------//
inline Rect::Rect()
    : X(0.0F)
    , Y(0.0F)
    , Width(0.0F)
    , Height(0.0F)
{
}
//------------------------------------------------------------------------------------------------//
inline Rect::Rect(float32_t value)
    : X(value)
    , Y(value)
    , Width(value)
    , Height(value)
{
}
//------------------------------------------------------------------------------------------------//
inline Rect::Rect(float32_t x, float32_t y, float32_t size)
    : X(x)
    , Y(y)
    , Width(size)
    , Height(size)
{
}
//------------------------------------------------------------------------------------------------//
inline Rect::Rect(float32_t x, float32_t y, float32_t width, float32_t height)
    : X(x)
    , Y(y)
    , Width(width)
    , Height(height)
{
}
//------------------------------------------------------------------------------------------------//
inline Rect::Rect(const Size& size)
    : X(0.0F)
    , Y(0.0F)
    , Width(size.Width)
    , Height(size.Height)
{
}
//------------------------------------------------------------------------------------------------//
inline Rect::Rect(const Point& point, const Vector& vector)
{
    if (point.X < vector.X)
    {
        X = point.X;
        Width = vector.X - point.X;
    }
    else
    {
        X = vector.X;
        Width = point.X - vector.X;
    }

    if (point.Y < vector.Y)
    {
        Y = point.Y;
        Height = vector.Y - point.Y;
    }
    else
    {
        Y = vector.Y;
        Height = point.Y - vector.Y;
    }
}
//------------------------------------------------------------------------------------------------//
inline Rect::Rect(const Point& point1, const Point& point2)
{
    if (point1.X < point2.X)
    {
        X = point1.X;
        Width = point2.X - point1.X;
    }
    else
    {
        X = point2.X;
        Width = point1.X - point2.X;
    }

    if (point1.Y < point2.Y)
    {
        Y = point1.Y;
        Height = point2.Y - point1.Y;
    }
    else
    {
        Y = point2.Y;
        Height = point1.Y - point2.Y;
    }
}
//------------------------------------------------------------------------------------------------//
inline Rect::Rect(const Point& location, const Size& size)
    : X(location.X)
    , Y(location.Y)
    , Width(size.Width)
    , Height(size.Height)
{
}
//------------------------------------------------------------------------------------------------//
inline bool Rect::operator == (const Rect& r) const
{
    return X == r.X &&
           Y == r.Y &&
           Width == r.Width &&
           Height == r.Height;
}
//------------------------------------------------------------------------------------------------//
inline bool Rect::operator != (const Rect& r) const
{
    return X != r.X ||
           Y != r.Y ||
           Width != r.Width ||
           Height != r.Height;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Rect::GetLeft() const
{
    return X;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Rect::GetTop() const
{
    return Y;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Rect::GetWidth() const
{
    return Width;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Rect::GetHeight() const
{
    return Height;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Rect::GetRight() const
{
    return X + Width;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Rect::GetBottom() const
{
    return Y + Height;
}
//------------------------------------------------------------------------------------------------//
inline Point Rect::GetLocation() const
{
    return Point(X, Y);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::SetLocation(const Point& value)
{
    X = value.X;
    Y = value.Y;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Size Rect::GetSize() const
{
    return Size(Width, Height);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::SetSize(const Size& size)
{
    Width = size.Width;
    Height = size.Height;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Point Rect::GetTopLeft() const
{
    return Point(X, Y);
}
//------------------------------------------------------------------------------------------------//
inline Point Rect::GetTopRight() const
{
    return Point(X + Width, Y);
}
//------------------------------------------------------------------------------------------------//
inline Point Rect::GetBottomLeft() const
{
    return Point(X, Y + Height);
}
//------------------------------------------------------------------------------------------------//
inline Point Rect::GetBottomRight() const
{
    return Point(X + Width, Y + Height);
}
//------------------------------------------------------------------------------------------------//
inline Point Rect::GetCenter() const
{
    return Point(X + (Width * 0.5F), Y + (Height * 0.5F));
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::SetCenter(const Point& value)
{
    X = value.X - Width * 0.5F;
    Y = value.Y - Height * 0.5F;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect Rect::CreateZeroRelative(float32_t width, float32_t height)
{
    return Rect(width * -0.5F, height * -0.5F, width, height);
}
//------------------------------------------------------------------------------------------------//
inline Rect Rect::CreateZeroRelative(const Size& size)
{
    return Rect(size.Width * -0.5F, size.Height * -0.5F, size.Width, size.Height);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Scale(const Size& size)
{
    X       *= size.Width;
    Y       *= size.Height;
    Width   *= size.Width;
    Height  *= size.Height;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Inflate(float32_t left, float32_t top, float32_t right, float32_t bottom)
{
    X -= left;
    Y -= top;
    Width += left + right;
    Height += top + bottom;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Inflate(float32_t horizontal, float32_t vertical)
{
    X -= horizontal;
    Y -= vertical;
    Width += horizontal + horizontal;
    Height += vertical + vertical;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Inflate(float32_t value)
{
    X -= value;
    Y -= value;
    Width += value + value;
    Height += value + value;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Inflate(const Size& size)
{
    return Inflate(size.Width, size.Height);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Inflate(const Thickness& value)
{
    return Rect::Inflate(
               value.Left,
               value.Top,
               value.Right,
               value.Bottom);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Deflate(float32_t left, float32_t top, float32_t right, float32_t bottom)
{
    X += left;
    Y += top;
    Width -= left + right;
    Height -= top + bottom;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Deflate(float32_t horizontal, float32_t vertical)
{
    X += horizontal;
    Y += vertical;
    Width -= horizontal + horizontal;
    Height -= vertical + vertical;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Deflate(float32_t value)
{
    X += value;
    Y += value;
    Width -= value + value;
    Height -= value + value;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Deflate(const Size& size)
{
    return Deflate(size.Width, size.Height);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Deflate(const Thickness& value)
{
    return Rect::Deflate(
               value.Left,
               value.Top,
               value.Right,
               value.Bottom);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Offset(float32_t x, float32_t y)
{
    X += x;
    Y += y;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Offset(const Vector& offset)
{
    X += offset.X;
    Y += offset.Y;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Intersect(const Rect& r)
{
    float32_t x = std::max(x, r.X);
    float32_t y = std::max(x, r.Y);
    float32_t width = std::min(GetRight(), r.GetRight()) - x;
    float32_t height = std::min(GetBottom(), r.GetBottom()) - y;

    if (width < 0.0F || height < 0.0F)
    {
        x = y = std::numeric_limits<float32_t>::infinity();
        width = height = -std::numeric_limits<float32_t>::infinity();
    }
    else
    {
        X = x;
        Y = y;
        Width = width;
        Height = height;
    }

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Union(const Rect& r)
{
    X = std::min(X, r.X);
    Y = std::min(Y, r.Y);
    Width = std::max(GetRight(), r.GetRight()) - X;
    Height = std::max(GetBottom(), r.GetBottom()) - Y;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline Rect& Rect::Union(const Point& p)
{
    X = std::min(X, p.X);
    Y = std::min(Y, p.Y);
    Width = std::max(GetRight(), p.X) - X;
    Height = std::min(GetBottom(), p.Y) - Y;

    return (*this);
}
//------------------------------------------------------------------------------------------------//
inline bool Rect::Contains(const Rect& r) const
{
    if (r.GetLeft() < GetLeft() || r.GetRight() > GetRight())
    {
        return false;
    }

    if (r.GetTop() < GetTop() || r.GetBottom() > GetBottom())
    {
        return false;
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
inline bool Rect::Contains(float32_t x, float32_t y) const
{
    if (x < GetLeft() || x > GetRight())
    {
        return false;
    }

    if (y < GetTop() || y > GetBottom())
    {
        return false;
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
inline bool Rect::Contains(const Point& point) const
{
    return Contains(point.X, point.Y);
}
//------------------------------------------------------------------------------------------------//
inline bool Rect::IntersectsWith(const Rect& r) const
{
    return !((GetLeft() >= r.GetRight()) || (GetRight() <= r.GetLeft()) ||
             (GetTop() >= r.GetBottom()) || GetBottom() <= r.GetTop());
}
//------------------------------------------------------------------------------------------------//
inline Point Rect::Clamp(const Point& p) const
{
    return Point(
               std::min(std::max(p.X, GetLeft()), GetRight()),
               std::min(std::max(p.Y, GetTop()), GetBottom()));
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
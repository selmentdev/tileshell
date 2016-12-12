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
#include <TileShell/Drawing/Size.h>
#include <TileShell/Drawing/Vector.h>
#include <TileShell/Drawing/Point.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
//------------------------------------------------------------------------------------------------//
inline Size::Size()
    : Width(0.0F)
    , Height(0.0F)
{
}
//------------------------------------------------------------------------------------------------//
inline Size::Size(const Size& size)
    : Width(size.Width)
    , Height(size.Height)
{
}
//------------------------------------------------------------------------------------------------//
inline Size::Size(float32_t width, float32_t height)
    : Width(width)
    , Height(height)
{
}
//------------------------------------------------------------------------------------------------//
inline Size::Size(float32_t size)
    : Width(size)
    , Height(size)
{
}
//------------------------------------------------------------------------------------------------//
inline bool Size::IsEmpty() const
{
    return Width == 0.0F && Height == 0.0F;
}
//------------------------------------------------------------------------------------------------//
inline bool Size::operator == (const Size& s) const
{
    return Width == s.Width && Height == s.Height;
}
//------------------------------------------------------------------------------------------------//
inline bool Size::operator != (const Size& s) const
{
    return Width != s.Width || Height != s.Height;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Size::GetAspectRatio() const
{
    return Width / Height;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Size::GetInverseAspectRatio() const
{
    return Height / Width;
}
//------------------------------------------------------------------------------------------------//
inline float32x2_t Size::ToFloat32x2() const
{
    return float32x2_t(Width, Height);
}
//------------------------------------------------------------------------------------------------//
inline float32x3_t Size::ToFloat32x3() const
{
    return float32x3_t(Width, Height, 0.0F);
}
//------------------------------------------------------------------------------------------------//
inline Point Size::ToPoint() const
{
    return Point(Width, Height);
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
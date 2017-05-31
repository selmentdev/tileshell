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
#ifndef _TileShell_Render_Size_H__
#define _TileShell_Render_Size_H__
//------------------------------------------------------------------------------------------------//
#include <tileshell.core/types.hxx>
#include <tileshell.drawing/point.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{

///
/// @brief
///     This struct represents size in 2D space.
///
struct Size
{
    float32_t   Width;
    float32_t   Height;

    Size();
    Size(const Size& size);
    Size(float32_t width, float32_t height);
    explicit Size(float32_t size);

public:
    bool IsEmpty() const;
    bool operator == (const Size& s) const;
    bool operator != (const Size& s) const;

public:
    float32_t GetAspectRatio() const;
    float32_t GetInverseAspectRatio() const;
    float32x2_t ToFloat32x2() const;
    float32x3_t ToFloat32x3() const;
    Point ToPoint() const;
};

}
}
//------------------------------------------------------------------------------------------------//
#include <tileshell.drawing/size.inl>
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Render_Size_H__ */
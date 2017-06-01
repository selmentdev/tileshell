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
#ifndef _TileShell_Render_Padding_H__
#define _TileShell_Render_Padding_H__

#include <tileshell.core/types.hxx>
#include <tileshell.drawing/size.hxx>

namespace TileShell::Drawing
{
    ///
    /// @brief
    ///     This struct represents thickness used as margin or padding in box model.
    ///
    struct Thickness
    {
        float32_t   Left;
        float32_t   Top;
        float32_t   Right;
        float32_t   Bottom;

        ///
        /// @brief
        ///     Creates instance of the Thickness struct.
        ///
        Thickness()
            : Left(0.0F)
            , Top(0.0F)
            , Right(0.0F)
            , Bottom(0.0F)
        {
        }

        ///
        /// @brief
        ///     Creates instance of the Thickness struct using other instance.
        ///
        Thickness(const Thickness& v)
            : Left(v.Left)
            , Top(v.Top)
            , Right(v.Right)
            , Bottom(v.Bottom)
        {
        }

        ///
        /// @brief
        ///     Creates instance of the Thickness struct.
        ///
        /// @param[in] horizontal
        ///     A horizontal thickness.
        /// @param[in] vertical
        ///     A vertical thickness.
        ///
        Thickness(float32_t horizontal, float32_t vertical)
            : Left(horizontal)
            , Top(vertical)
            , Right(horizontal)
            , Bottom(vertical)
        {
        }

        ///
        /// @brief
        ///     Creates instance of the Thickness struct.
        ///
        /// @param[in] padding
        ///     A value used for all components.
        ///
        explicit Thickness(float32_t padding)
            : Left(padding)
            , Top(padding)
            , Right(padding)
            , Bottom(padding)
        {
        }

        ///
        /// @brief
        ///     Creates instance of the Thickness struct.
        ///
        /// @param[in] left
        ///     A left thickness value.
        /// @param[in] top
        ///     A top thickness value.
        /// @param[in] right
        ///     A right thickness value.
        /// @param[in] bottom
        ///     A bottom thickness value.
        ///
        Thickness(float32_t left, float32_t top, float32_t right, float32_t bottom)
            : Left(left)
            , Top(top)
            , Right(right)
            , Bottom(bottom)
        {
        }

        ///
        /// Scales current Thickness instance.
        ///
        /// @param[in] size
        ///     A scale of the thickness.
        ///
        Thickness& Scale(const Size& size)
        {
            Left *= size.Width;
            Top *= size.Height;
            Right *= size.Width;
            Bottom *= size.Height;

            return (*this);
        }
    };
}

#endif /* _TileShell_Render_Padding_H__ */
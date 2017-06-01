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
#ifndef _TileShell_Render_Transform2D_H__
#define _TileShell_Render_Transform2D_H__

#include <tileshell/required.hxx>
#include <tileshell.core/types.hxx>
#include <tileshell.drawing/matrix.hxx>

namespace TileShell::Drawing
{

    ///
    /// @brief
    ///     The scale transform.
    ///
    struct ScaleTransform
    {
        float32_t   ScaleX;
        float32_t   ScaleY;

        ScaleTransform()
            : ScaleX(1.0F)
            , ScaleY(1.0F)
        {
        }

        ScaleTransform(float32_t scale_x, float32_t scale_y)
            : ScaleX(scale_x)
            , ScaleY(scale_y)
        {
        }
    };

    ///
    /// @brief
    ///     Skew transform.
    ///
    struct SkewTransform
    {
        float32_t   AngleX;
        float32_t   AngleY;

        SkewTransform()
            : AngleX(0.0F)
            , AngleY(0.0F)
        {
        }

        SkewTransform(float32_t angle_x, float32_t angle_y)
            : AngleX(angle_x)
            , AngleY(angle_y)
        {
        }
    };

    ///
    /// @brief
    ///     Translate transform.
    ///
    struct TranslateTransform
    {
        float32_t   X;
        float32_t   Y;

        TranslateTransform()
            : X(0.0F)
            , Y(0.0F)
        {
        }

        TranslateTransform(float32_t x, float32_t y)
            : X(x)
            , Y(y)
        {
        }
    };

    ///
    /// @brief
    ///     Rotate transform.
    ///
    struct RotateTransform
    {
        float32_t   Angle;

        RotateTransform()
            : Angle(0.0F)
        {
        }

        RotateTransform(float32_t angle)
            : Angle(angle)
        {
        }
    };

    ///
    /// @brief
    ///     Visual transform.
    ///
    struct Transform
    {
        ///
        /// Translate transform.
        ///
        TranslateTransform  Translate;

        ///
        /// Rotate transform.
        ///
        RotateTransform     Rotate;

        ///
        /// Scale transform.
        ///
        ScaleTransform      Scale;

        ///
        /// Skew transform.
        ///
        SkewTransform       Skew;

        ///
        /// Computes transform matrix for this transform.
        ///
        void ComputeTransformMatrix(Matrix& out_result);

        ///
        /// Computes transform matrix for this transform, using specified transform origin point.
        ///
        void ComputeTransformMatrix(Matrix& out_result, const Point& in_transform_origin);

        ///
        /// Computes transform matrix for this transform, using rectangle.
        ///
        /// @todo
        ///     By passing rectangle, we can specify origin point for each single transform at
        ///     different point.
        ///
        void ComputeTransformMatrix(Matrix& out_result, const Rect& in_rectangle);
    };
    static_assert(sizeof(Transform) == 28, "Transform size mismatch");
}

#endif /* _TileShell_Render_Transform2D_H__ */
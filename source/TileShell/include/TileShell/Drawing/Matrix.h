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
#ifndef _TileShell_Drawing_Matrix_H__
#define _TileShell_Drawing_Matrix_H__
//------------------------------------------------------------------------------------------------//
#include <TileShell/Core/Types.h>
#include <TileShell/Drawing/Rect.h>
#include <TileShell/Drawing/Point.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
///
/// Matrix concatenation order.
///
enum MatrixOrder
{
    MatrixOrder_Append,
    MatrixOrder_Prepend
};

///
/// Represents 2x3 affine transformation matrix in 2D space.
///
struct Matrix
{
    float32_t   M11;
    float32_t   M12;
    float32_t   M21;
    float32_t   M22;
    float32_t   DX;
    float32_t   DY;

    ///
    /// Creates instance of the Matrix struct containing identity matrix.
    ///
    Matrix();

    ///
    /// Creates instance of the Matrix struct using provided matrix components.
    ///
    Matrix(float32_t m11, float32_t m12, float32_t m21, float32_t m22, float32_t dx, float32_t dy);

    ///
    /// Creates instance of the Matrix struct using another Matrix struct instance.
    ///
    Matrix(const Matrix& m);

    ///
    /// Creates instance of Matrix struct as transformation from rectangle to poly.
    ///
    Matrix(const Rect& rect, const Point& p1, const Point& p2, const Point& p3);

public:
    bool operator == (const Matrix& m) const;
    bool operator != (const Matrix& m) const;

public:
    ///
    /// Gets value indicating whether matrix is identity matrix.
    ///
    bool IsIdentity() const;

    ///
    /// Gets value indicating whether matrix is invertible.
    ///
    bool IsInvertible() const;

    ///
    /// Gets X offset value.
    ///
    float32_t GetOffsetX() const;

    ///
    /// Gets Y offset value.
    ///
    float32_t GetOffsetY() const;

    ///
    /// Gets matrix determinant.
    ///
    float32_t Determinant() const;

public:

    ///
    /// Transforms point.
    ///
    float32x2_t TransformPoint(float32x2_t point) const;

    ///
    /// Transforms point.
    ///
    float32x3_t TransformPoint(float32x3_t point) const;

    ///
    /// Transforms array of 2D points.
    ///
    void TransformPoints(float32x2_t points[], size_t count) const;

    ///
    /// Transforms array of 3D points.
    ///
    void TransformPoints(float32x3_t points[], size_t count) const;

    ///
    /// Transforms array of 2D vectors.
    ///
    void TransformVectors(float32x2_t points[], size_t count) const;

    ///
    /// Transforms array of 3D vectors.
    ///
    void TransformVectors(float32x3_t points[], size_t count) const;

    ///
    /// Transforms font size.
    ///
    float32_t TransformFontSize(float32_t value) const;

public:

    ///
    /// Inverts matrix.
    ///
    /// @returns
    ///     true when matrix was invertible, false otherwise.
    ///
    bool Invert();

    ///
    /// Multiplies two matrices and returns result matrix: out_result = in_m1 * in_m2
    ///
    /// @param[out] out_result
    ///     A result matrix.
    /// @param[in] in_m1
    ///     A source matrix.
    /// @param[in] in_m2
    ///     A source matrix.
    ///
    static void Multiply(Matrix& out_result, const Matrix& in_m1, const Matrix& in_m2);

    ///
    /// Multiplies this matrix by another.
    ///
    void Multiply(const Matrix& in_matrix);

    ///
    /// Multiplies this matrix by another using specific matrix multiplying order.
    ///
    void Multiply(const Matrix& in_matrix, MatrixOrder order);

    ///
    /// Resets matrix.
    ///
    void Reset();

    ///
    /// Rotate matrix transform.
    ///
    void Rotate(float32_t angle);

    ///
    /// Rotate matrix transform.
    ///
    void Rotate(float32_t angle, MatrixOrder order);

    ///
    /// Rotate matrix transform at specific point.
    ///
    void RotateAt(float32_t angle, float32x2_t point);

    ///
    /// Rotate matrix transform at specific point.
    ///
    void RotateAt(float32_t angle, float32x2_t point, MatrixOrder order);

    ///
    /// Translates matrix.
    ///
    void Translate(float32_t offset_x, float32_t offset_y);

    ///
    /// Translates matrix.
    ///
    void Translate(float32_t offset_x, float32_t offset_y, MatrixOrder order);

    ///
    /// Scales matrix.
    ///
    void Scale(float32_t scale_x, float32_t scale_y);

    ///
    /// Scales matrix.
    ///
    void Scale(float32_t scale_x, float32_t scale_y, MatrixOrder order);

    ///
    /// Scales matrix at specified point.
    ///
    void ScaleAt(float32_t scale_x, float32_t scale_y, float32x2_t point);

    ///
    /// Scales matrix at specified point.
    ///
    void ScaleAt(float32_t scale_x, float32_t scale_y, float32x2_t point, MatrixOrder order);

    ///
    /// Shears matrix.
    ///
    void Shear(float32_t shear_x, float32_t shear_y);

    ///
    /// Shears matrix.
    ///
    void Shear(float32_t shear_x, float32_t shear_y, MatrixOrder order);

    ///
    /// Shears matrix at specified point.
    ///
    void ShearAt(float32_t shear_x, float32_t shear_y, float32x2_t point);

    ///
    /// Shears matrix at specified point.
    ///
    void ShearAt(float32_t shear_x, float32_t shear_y, float32x2_t point, MatrixOrder order);

private:
    ///
    /// Generates transformation matrix from speicied rectangle and points.
    ///
    void TransformationFromRectangleToPoly(
        const Rect& rect, const Point& p1, const Point& p2, const Point& p3);
};
static_assert(sizeof(Matrix) == 24, "sizeof(Matrix) != 24");
//------------------------------------------------------------------------------------------------//
inline Matrix::Matrix()
    : M11(1.0F)
    , M12(0.0F)
    , M21(0.0F)
    , M22(1.0F)
    , DX(0.0F)
    , DY(0.0F)
{
}
//------------------------------------------------------------------------------------------------//
inline Matrix::Matrix(float32_t m11, float32_t m12, float32_t m21, float32_t m22, float32_t dx,
                      float32_t dy)
    : M11(m11)
    , M12(m12)
    , M21(m21)
    , M22(m22)
    , DX(dx)
    , DY(dy)
{
}
//------------------------------------------------------------------------------------------------//
inline Matrix::Matrix(const Matrix& m)
    : M11(m.M11)
    , M12(m.M12)
    , M21(m.M21)
    , M22(m.M22)
    , DX(m.DX)
    , DY(m.DY)
{
}
//------------------------------------------------------------------------------------------------//
inline Matrix::Matrix(const Rect& rect, const Point& p1, const Point& p2, const Point& p3)
{
    TransformationFromRectangleToPoly(rect, p1, p2, p3);
}
//------------------------------------------------------------------------------------------------//
inline bool Matrix::operator == (const Matrix& m) const
{
    return
        this->M11 == m.M11 &&
        this->M12 == m.M12 &&
        this->M21 == m.M21 &&
        this->M22 == m.M22 &&
        this->DX  == m.DX  &&
        this->DY  == m.DY;
}
//------------------------------------------------------------------------------------------------//
inline bool Matrix::operator != (const Matrix& m) const
{
    return
        this->M11 != m.M11 ||
        this->M12 != m.M12 ||
        this->M21 != m.M21 ||
        this->M22 != m.M22 ||
        this->DX  != m.DX  ||
        this->DY  != m.DY;
}
//------------------------------------------------------------------------------------------------//
inline bool Matrix::IsIdentity() const
{
    return M11 == 1.0F &&
           M12 == 0.0F &&
           M21 == 0.0F &&
           M22 == 1.0F &&
           DX == 0.0F &&
           DY == 0.0F;
}
//------------------------------------------------------------------------------------------------//
inline bool Matrix::IsInvertible() const
{
    return Determinant() != 0.0F;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Matrix::GetOffsetX() const
{
    return DX;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Matrix::GetOffsetY() const
{
    return DY;
}
//------------------------------------------------------------------------------------------------//
inline float32_t Matrix::Determinant() const
{
    return M11 * M22 - M12 * M21;
}
//------------------------------------------------------------------------------------------------//
inline float32x2_t Matrix::TransformPoint(float32x2_t point) const
{
    return float32x2_t(
               point.X * M11 + point.Y * M21 + DX,
               point.X * M21 + point.Y * M22 + DY);
}
//------------------------------------------------------------------------------------------------//
inline float32x3_t Matrix::TransformPoint(float32x3_t point) const
{
    return float32x3_t(
               point.X * M11 + point.Y * M21 + DX,
               point.X * M21 + point.Y * M22 + DY,
               point.Z);
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::TransformPoints(float32x2_t points[], size_t count) const
{
    float32_t x, y;

    for (size_t i = 0; i != count; ++i)
    {
        x = points[i].X;
        y = points[i].Y;
        points[i].X = x * M11 + y * M21 + DX;
        points[i].Y = x * M12 + y * M22 + DY;
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::TransformPoints(float32x3_t points[], size_t count) const
{
    float32_t x, y;

    for (size_t i = 0; i != count; ++i)
    {
        x = points[i].X;
        y = points[i].Y;
        points[i].X = x * M11 + y * M21 + DX;
        points[i].Y = x * M12 + y * M22 + DY;
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::TransformVectors(float32x2_t points[], size_t count) const
{
    float32_t x, y;

    for (size_t i = 0; i != count; ++i)
    {
        x = points[i].X;
        y = points[i].Y;
        points[i].X = x * M11 + y * M21;
        points[i].Y = x * M12 + y * M22;
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::TransformVectors(float32x3_t points[], size_t count) const
{
    float32_t x, y;

    for (size_t i = 0; i != count; ++i)
    {
        x = points[i].X;
        y = points[i].Y;
        points[i].X = x * M11 + y * M21;
        points[i].Y = x * M12 + y * M22;
    }
}
//------------------------------------------------------------------------------------------------//
inline float32_t Matrix::TransformFontSize(float32_t value) const
{
    return std::abs(std::min(M11, M22) * value);
}
//------------------------------------------------------------------------------------------------//
inline bool Matrix::Invert()
{
    float32_t m11, m12, m21, m22, dx, dy;
    float32_t det = Determinant();

    if (det != 0.0F)
    {
        m11 = M22 / det;
        m12 = -(M12 / det);
        m21 = -(M21 / det);
        m22 = M11 / det;

        dx = (M21 * DY - M22 * DX) / det;
        dy = (M12 * DX - M11 * DY) / det;

        M11 = m11;
        M12 = m12;
        M21 = m21;
        M22 = m22;
        DX = dx;
        DY = dy;

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Multiply(Matrix& out_result, const Matrix& in_m1, const Matrix& in_m2)
{
    float32_t m11, m12, m21, m22, dx, dy;

    m11 = in_m1.M11 * in_m2.M11 + in_m1.M12 * in_m2.M21;
    m12 = in_m1.M11 * in_m2.M12 + in_m1.M12 * in_m2.M22;
    m21 = in_m1.M21 * in_m2.M11 + in_m1.M22 * in_m2.M21;
    m22 = in_m1.M21 * in_m2.M12 + in_m1.M22 * in_m2.M22;
    dx  = in_m1.DX  * in_m2.M11 + in_m1.DY  * in_m2.M21 + in_m2.DX;
    dy  = in_m1.DX  * in_m2.M12 + in_m1.DY  * in_m2.M22 + in_m2.DY;

    out_result.M11 = m11;
    out_result.M12 = m12;
    out_result.M21 = m21;
    out_result.M22 = m22;
    out_result.DX = dx;
    out_result.DY = dy;
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Multiply(const Matrix& in_matrix)
{
    Multiply(*this, *this, in_matrix);
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Multiply(const Matrix& in_matrix, MatrixOrder order)
{
    if (order == MatrixOrder_Prepend)
    {
        Multiply(*this, in_matrix, *this);
    }
    else
    {
        Multiply(*this, *this, in_matrix);
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Reset()
{
    M11 = 1.0F;
    M12 = 0.0F;
    M21 = 0.0F;
    M22 = 1.0F;
    DX = 0.0F;
    DY = 0.0F;
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Rotate(float32_t angle)
{
    float32_t radians = (angle * (3.14159F / 180.0F));
    float32_t cos = std::cos(radians);
    float32_t sin = std::sin(radians);

    float32_t m11 = cos * M11 + sin * M21;
    float32_t m12 = cos * M12 + sin * M22;
    float32_t m21 = cos * M21 - sin * M11;
    float32_t m22 = cos * M22 - sin * M12;

    M11 = m11;
    M12 = m12;
    M21 = m21;
    M22 = m22;
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Rotate(float32_t angle, MatrixOrder order)
{
    float32_t radians = (angle * (3.14159F / 180.0F));
    float32_t cos = std::cos(radians);
    float32_t sin = std::sin(radians);

    if (order == MatrixOrder_Prepend)
    {
        float32_t m11 = cos * M11 + sin * M21;
        float32_t m12 = cos * M12 + sin * M22;
        float32_t m21 = cos * M21 - sin * M11;
        float32_t m22 = cos * M22 - sin * M12;

        M11 = m11;
        M12 = m12;
        M21 = m21;
        M22 = m22;
    }
    else
    {
        float32_t m11 = M11 * cos - M12 * sin;
        float32_t m12 = M11 * sin + M12 * cos;
        float32_t m21 = M21 * cos - M22 * sin;
        float32_t m22 = M21 * sin + M22 * cos;
        float32_t dx = DX * cos - DY * sin;
        float32_t dy = DX * sin + DY * cos;

        M11 = m11;
        M12 = m12;
        M21 = m21;
        M22 = m22;
        DX = dx;
        DY = dy;
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::RotateAt(float32_t angle, float32x2_t point)
{
    Translate(point.X, point.Y);
    Rotate(angle);
    Translate(-point.X, -point.Y);
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::RotateAt(float32_t angle, float32x2_t point, MatrixOrder order)
{
    if (order == MatrixOrder_Prepend)
    {
        Translate(point.X, point.Y);
        Rotate(angle);
        Translate(-point.X, -point.Y);
    }
    else
    {
        Translate(-point.X, -point.Y);
        Rotate(angle, MatrixOrder_Append);
        Translate(point.X, point.Y);
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Translate(float32_t offset_x, float32_t offset_y)
{
    DX += offset_x * M11 + offset_y * M21;
    DY += offset_x * M12 + offset_y * M22;
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Translate(float32_t offset_x, float32_t offset_y, MatrixOrder order)
{
    if (order == MatrixOrder_Prepend)
    {
        DX += offset_x * M11 + offset_y * M21;
        DY += offset_x * M12 + offset_y * M22;
    }
    else
    {
        DX += offset_x;
        DY += offset_y;
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Scale(float32_t scale_x, float32_t scale_y)
{
    M11 *= scale_x;
    M12 *= scale_x;
    M21 *= scale_y;
    M22 *= scale_y;
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Scale(float32_t scale_x, float32_t scale_y, MatrixOrder order)
{
    if (order == MatrixOrder_Prepend)
    {
        M11 *= scale_x;
        M12 *= scale_x;
        M21 *= scale_y;
        M22 *= scale_y;
    }
    else
    {
        M11 *= scale_x;
        M12 *= scale_y;
        M21 *= scale_x;
        M22 *= scale_y;
        DX *= scale_x;
        DY *= scale_y;
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::ScaleAt(float32_t scale_x, float32_t scale_y, float32x2_t point)
{
    Translate(point.X, point.Y);
    Scale(scale_x, scale_y);
    Translate(-point.X, -point.Y);
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::ScaleAt(float32_t scale_x, float32_t scale_y, float32x2_t point,
                            MatrixOrder order)
{
    if (order == MatrixOrder_Prepend)
    {
        Translate(point.X, point.Y);
        Scale(scale_x, scale_y);
        Translate(-point.X, -point.Y);
    }
    else
    {
        Translate(-point.X, -point.Y);
        Scale(scale_x, scale_y, MatrixOrder_Append);
        Translate(point.X, point.Y);
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Shear(float32_t shear_x, float32_t shear_y)
{
    float32_t m11 = M11 + M21 * shear_y;
    float32_t m12 = M12 + M22 * shear_y;
    float32_t m21 = M11 * shear_x + M21;
    float32_t m22 = M12 * shear_x + M22;

    M11 = m11;
    M12 = m12;
    M21 = m21;
    M22 = m22;
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::Shear(float32_t shear_x, float32_t shear_y, MatrixOrder order)
{
    if (order == MatrixOrder_Prepend)
    {
        float32_t m11 = M11 + M21 * shear_y;
        float32_t m12 = M12 + M22 * shear_y;
        float32_t m21 = M11 * shear_x + M21;
        float32_t m22 = M12 * shear_x + M22;

        M11 = m11;
        M12 = m12;
        M21 = m21;
        M22 = m22;
    }
    else
    {
        float32_t m11 = M11 + M12 * shear_x;
        float32_t m12 = M11 * shear_y + M12;
        float32_t m21 = M21 + M22 * shear_x;
        float32_t m22 = M21 * shear_y + M22;
        float32_t dx = DX + DY * shear_x;
        float32_t dy = DX * shear_y + DY;

        M11 = m11;
        M12 = m12;
        M21 = m21;
        M22 = m22;
        DX = dx;
        DY = dy;
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::ShearAt(float32_t shear_x, float32_t shear_y, float32x2_t point)
{
    Translate(point.X, point.Y);
    Shear(shear_x, shear_y);
    Translate(-point.X, -point.Y);
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::ShearAt(float32_t shear_x, float32_t shear_y, float32x2_t point,
                            MatrixOrder order)
{
    if (order == MatrixOrder_Prepend)
    {
        Translate(point.X, point.Y);
        Shear(shear_x, shear_y);
        Translate(-point.X, -point.Y);
    }
    else
    {
        Translate(-point.X, -point.Y);
        Shear(shear_x, shear_y, MatrixOrder_Append);
        Translate(point.X, point.Y);
    }
}
//------------------------------------------------------------------------------------------------//
inline void Matrix::TransformationFromRectangleToPoly(
    const Rect& rect, const Point& p1, const Point& p2, const Point& p3)
{
    Point v1(p2.X - p1.X, p2.Y - p1.Y);
    Point v2(p3.X - p1.X, p3.Y - p1.Y);

    this->DX = p1.X - rect.X / rect.Width * v1.X - rect.Y / rect.Height * v2.X;
    this->DY = p1.Y - rect.X / rect.Width * v1.Y - rect.Y / rect.Height * v2.Y;

    this->M11 = v1.X / rect.Width;
    this->M12 = v1.Y / rect.Width;
    this->M21 = v2.X / rect.Height;
    this->M22 = v2.Y / rect.Height;
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Drawing_Matrix_H__ */
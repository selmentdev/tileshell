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
#include <TileShell/Drawing/Transform.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
//------------------------------------------------------------------------------------------------//
void Transform::ComputeTransformMatrix(Matrix& out_result)
{
    out_result.Reset();
    out_result.Shear(Skew.AngleX, Skew.AngleY);
    out_result.Scale(Scale.ScaleX, Scale.ScaleY);
    out_result.Rotate(Rotate.Angle);
    out_result.Translate(Translate.X, Translate.Y);
}
//------------------------------------------------------------------------------------------------//
void Transform::ComputeTransformMatrix(Matrix& out_result, const Point& in_transform_origin)
{
#if 1
    out_result.Reset();
    out_result.Translate(in_transform_origin.X, in_transform_origin.Y);
    {
        out_result.Translate(Translate.X, Translate.Y);
        out_result.Rotate(Rotate.Angle);
        out_result.Shear(Skew.AngleX, Skew.AngleY);
        out_result.Scale(Scale.ScaleX, Scale.ScaleY);

    }
    out_result.Translate(-in_transform_origin.X, -in_transform_origin.Y);

#else
    out_result.Shear(Skew.AngleX, Skew.AngleY);
    out_result.Scale(Scale.ScaleX, Scale.ScaleY);
    out_result.RotateAt(Rotate.Angle, in_transform_origin.ToFloat32x2());
    out_result.Translate(Translate.X, Translate.Y);

#endif
}
//------------------------------------------------------------------------------------------------//
void Transform::ComputeTransformMatrix(Matrix& out_result, const Rect& in_rectangle)
{
#if 0
    float32x2_t shear_origin = in_transform_origin.GetCenter().ToFloat32x2();
    float32x2_t scale_origin = in_transform_origin.GetCenter().ToFloat32x2();
    float32x2_t rotate_origin = in_transform_origin.GetCenter().ToFloat32x2();

    out_result.Reset();
    //out_result.Translate(in_transform_origin.X, in_transform_origin.Y);
    {
        out_result.ShearAt(Skew.AngleX, Skew.AngleY, shear_origin);
        out_result.ScaleAt(Scale.ScaleX, Scale.ScaleY, scale_origin);
        out_result.RotateAt(Rotate.Angle, rotate_origin);
        out_result.Translate(Translate.X, Translate.Y);
    }
    //out_result.Translate(-in_transform_origin.X, -in_transform_origin.Y);
#else
    ComputeTransformMatrix(out_result, in_rectangle.GetCenter());
#endif
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
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
#include <tileshell.ui/visual.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
//------------------------------------------------------------------------------------------------//
inline const Drawing::Transform& Visual::GetTransform() const
{
    return _transform;
}
//------------------------------------------------------------------------------------------------//
inline const Drawing::SkewTransform& Visual::GetSkewTransform() const
{
    return _transform.Skew;
}
//------------------------------------------------------------------------------------------------//
inline const Drawing::ScaleTransform& Visual::GetScaleTransform() const
{
    return _transform.Scale;
}
//------------------------------------------------------------------------------------------------//
inline const Drawing::RotateTransform& Visual::GetRotateTransform() const
{
    return _transform.Rotate;
}
//------------------------------------------------------------------------------------------------//
inline const Drawing::TranslateTransform& Visual::GetTranslateTransform() const
{
    return _transform.Translate;
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetTransform(const Drawing::Transform& value)
{
    _transform = value;

    OnPropertyChanged(Core::StrongName("Transform"));
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetSkewTransform(const Drawing::SkewTransform& value)
{
    _transform.Skew = value;
    OnPropertyChanged(Core::StrongName("SkewTransform"));
    OnPropertyChanged(Core::StrongName("Transform"));
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetScaleTransform(const Drawing::ScaleTransform& value)
{
    _transform.Scale = value;
    OnPropertyChanged(Core::StrongName("ScaleTransform"));
    OnPropertyChanged(Core::StrongName("Transform"));
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetRotateTransform(const Drawing::RotateTransform& value)
{
    _transform.Rotate = value;
    OnPropertyChanged(Core::StrongName("RotateTransform"));
    OnPropertyChanged(Core::StrongName("Transform"));
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetTranslateTransform(const Drawing::TranslateTransform& value)
{
    _transform.Translate = value;
    OnPropertyChanged(Core::StrongName("TranslateTransform"));
    OnPropertyChanged(Core::StrongName("Transform"));
}
//------------------------------------------------------------------------------------------------//
inline const Drawing::Matrix& Visual::GetTransformMatrix() const
{
    return _local_transform_matrix;
}
//------------------------------------------------------------------------------------------------//
inline const Drawing::Size& Visual::GetSize() const
{
    return _rectangle.GetSize();
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetSize(const Drawing::Size& value)
{
    _rectangle.SetSize(value);
    OnPropertyChanged(Core::StrongName("Size"));
    OnPropertyChanged(Core::StrongName("Transform"));
}
//------------------------------------------------------------------------------------------------//
inline const Drawing::Point& Visual::GetLocation() const
{
    return _rectangle.GetLocation();
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetLocation(const Drawing::Point& value)
{
    _rectangle.SetLocation(value);
    OnPropertyChanged(Core::StrongName("Location"));
    OnPropertyChanged(Core::StrongName("Transform"));
}
//------------------------------------------------------------------------------------------------//
inline const Drawing::Rect& Visual::GetRectangle() const
{
    return _rectangle;
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetRectangle(const Drawing::Rect& value)
{
    _rectangle = value;
    OnPropertyChanged(Core::StrongName("Location"));
    OnPropertyChanged(Core::StrongName("Size"));
    OnPropertyChanged(Core::StrongName("Transform"));
}
//------------------------------------------------------------------------------------------------//
inline const Drawing::Thickness& Visual::GetPadding() const
{
    return _padding;
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetPadding(const Drawing::Thickness& value)
{
    _padding = value;
    OnPropertyChanged(Core::StrongName("Padding"));
}
//------------------------------------------------------------------------------------------------//
inline const Drawing::StyleRef Visual::GetStyle() const
{
    return _style;
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetStyle(const Drawing::StyleRef& value)
{
    _style = value;

    OnPropertyChanged(Core::StrongName("Style"));
}
//------------------------------------------------------------------------------------------------//
inline const Core::StrongName& Visual::GetName() const
{
    return _name;
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetName(const Core::StrongName& value)
{
    _name = value;

    OnPropertyChanged(Core::StrongName("Name"));
}
//------------------------------------------------------------------------------------------------//
inline float32_t Visual::GetOpacity() const
{
    return _opacity;
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetOpacity(float32_t value)
{
    _opacity = value;
    OnPropertyChanged(Core::StrongName("Opacity"));
}
//------------------------------------------------------------------------------------------------//
inline bool Visual::GetVisibility() const
{
    return _visibility;
}
//------------------------------------------------------------------------------------------------//
inline void Visual::SetVisibility(bool value)
{
    _visibility = value;
    OnPropertyChanged(Core::StrongName("Visibility"));
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
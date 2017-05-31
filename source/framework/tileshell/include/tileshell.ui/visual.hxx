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
#include <tileshell.ui/ielement.hxx>
#include <tileshell.ui/inotifypropertychanged.hxx>
#include <tileshell.drawing/transform.hxx>
#include <tileshell.drawing/size.hxx>
#include <tileshell.drawing/point.hxx>
#include <tileshell.drawing/rect.hxx>
#include <tileshell.drawing/thickness.hxx>
#include <tileshell.core/strongname.hxx>
#include <tileshell.drawing/style.hxx>
#include <tileshell.drawing/styleitem.hxx>
#include <tileshell.drawing/matrix.hxx>
#include <tileshell.drawing/color.hxx>
#include <tileshell.drawing/font.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
///
/// @brief
///     Visual object.
///
/// @details
///     This class declares properties that are common to visual objects rendered by library.
///
///
/// @note
///     This class defines an visual element, that can be separately rendered in 3D space. Note that
///     element itself is 2D planar object, but can be rendered using separate 4x4 matrix containing
///     it's world transformation in 3D.
///
/// @note
///     Every transformation assigned to this element is in 2D space.
///
class Visual
    : public IElement
    , public INotifyPropertyChanged
{
protected:
    Drawing::Transform  _transform;         // Transform (2D)
    float32_t           _opacity;           // Opacity value
    Drawing::Rect       _rectangle;         // Element rectangle
    Drawing::Thickness  _padding;           // Padding
    Drawing::Matrix     _local_transform_matrix;  // Matrix built from transform (2D)
    Drawing::StyleRef   _style;             // Reference to used style
    Core::StrongName    _name;              // Strong name of visual element
    bool                _visibility;        // Visibility

public:
    ///
    /// @brief
    ///     Creates instance of the Visual class.
    ///
    Visual();

    ///
    /// @brief
    ///     Destroys instance of the Visual class.
    ///
    virtual ~Visual();

public:
    ///
    /// @brief
    ///     Gets transform.
    ///
    const Drawing::Transform& GetTransform() const;

    ///
    /// @brief
    ///     Gets skew transform.
    ///
    const Drawing::SkewTransform& GetSkewTransform() const;

    ///
    /// @brief
    ///     Gets scale transform.
    ///
    const Drawing::ScaleTransform& GetScaleTransform() const;

    ///
    /// @brief
    ///     Gets rotate transform.
    ///
    const Drawing::RotateTransform& GetRotateTransform() const;

    ///
    /// @brief
    ///     Gets translate transform.
    ///
    const Drawing::TranslateTransform& GetTranslateTransform() const;

    ///
    /// @brief
    ///     Sets transform.
    ///
    void SetTransform(const Drawing::Transform& value);

    ///
    /// @brief
    ///     Sets skew transform.
    ///
    void SetSkewTransform(const Drawing::SkewTransform& value);

    ///
    /// @brief
    ///     Sets scale transform.
    ///
    void SetScaleTransform(const Drawing::ScaleTransform& value);

    ///
    /// @brief
    ///     Set rotate transform.
    ///
    void SetRotateTransform(const Drawing::RotateTransform& value);

    ///
    /// @brief
    ///     Sets translate transform.
    ///
    void SetTranslateTransform(const Drawing::TranslateTransform& value);

    ///
    /// @brief
    ///     Gets transform matrix.
    ///
    const Drawing::Matrix& GetTransformMatrix() const;

    ///
    /// @brief
    ///     Gets size.
    ///
    const Drawing::Size& GetSize() const;

    ///
    /// @brief
    ///     Sets size.
    ///
    void SetSize(const Drawing::Size& value);

    ///
    /// @brief
    ///     Gets location.
    ///
    const Drawing::Point& GetLocation() const;

    ///
    /// @brief
    ///     Sets location.
    ///
    void SetLocation(const Drawing::Point& value);

    ///
    /// @brief
    ///     Gets rectangle.
    ///
    const Drawing::Rect& GetRectangle() const;

    ///
    /// @brief
    ///     Sets rectangle.
    ///
    void SetRectangle(const Drawing::Rect& value);

    ///
    /// @brief
    ///     Gets padding.
    ///
    const Drawing::Thickness& GetPadding() const;

    ///
    /// @brief
    ///     Sets padding.
    ///
    void SetPadding(const Drawing::Thickness& value);

    ///
    /// @brief
    ///     Gets style.
    ///
    const Drawing::StyleRef GetStyle() const;

    ///
    /// @brief
    ///     Sets style.
    ///
    void SetStyle(const Drawing::StyleRef& value);

    ///
    /// @brief
    ///     Gets name.
    ///
    const Core::StrongName& GetName() const;

    ///
    /// @brief
    ///     Sets name.
    ///
    void SetName(const Core::StrongName& value);

    ///
    /// @brief
    ///     Gets opacity.
    ///
    float32_t GetOpacity() const;

    ///
    /// @brief
    ///     Sets opacity.
    ///
    void SetOpacity(float32_t value);

    ///
    /// @brief
    ///     Gets visibility.
    ///
    bool GetVisibility() const;

    ///
    /// @brief
    ///     Sets visibility.
    ///
    void SetVisibility(bool value);

public:
    virtual bool Deserialize(Xml::XmlNode* node) override;

    virtual bool OnPropertyChanged(const Core::StrongName& property_name) override;
};
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
#include <tileshell.ui/visual.inl>
//------------------------------------------------------------------------------------------------//
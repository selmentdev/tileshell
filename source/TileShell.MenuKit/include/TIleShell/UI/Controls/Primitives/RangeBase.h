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

#include <TileShell/UI/Controls/Control.h>
#include <TileShell/Serialization/TypeSerializer.h>

namespace TileShell
{
namespace UI
{
namespace Controls
{
namespace Primitives
{
///
/// @brief
///     This class implements base logic for range controls.
///
class RangeBase
    : public Control
{
protected:
    float32_t       _range_min;
    float32_t       _range_max;
    float32_t       _range_small_step;
    float32_t       _range_large_step;
    float32_t       _value;
    float32_t       _default_value;
    Orientation     _orientation;

public:
    RangeBase();
    virtual ~RangeBase();

public:
    ///
    /// @brief
    ///     Gets range min.
    ///
    float32_t GetRangeMin() const;

    ///
    /// @brief
    ///     Sets range min.
    ///
    void SetRangeMin(float32_t value);

    ///
    /// @brief
    ///     Gets range max.
    ///
    float32_t GetRangeMax() const;

    ///
    /// @brief
    ///     Sets range max.
    ///
    void SetRangeMax(float32_t value);

    float32_t GetSmallStepValue() const;
    void SetSmallStepValue(float32_t value);

    float32_t GetLargeStepValue() const;
    void SetLargeStepValue(float32_t value);

    ///
    /// @brief
    ///     Gets value.
    ///
    float32_t GetValue() const;

    ///
    /// @brief
    ///     Sets value.
    ///
    void SetValue(float32_t value);

    ///
    /// @brief
    ///     Resets value to default value.
    ///
    void ResetValue();

    ///
    /// @brief
    ///     Gets percentage value.
    ///
    float32_t GetPercentage() const;

    ///
    /// @brief
    ///     Gets orientation.
    ///
    Orientation GetOrientation() const;

    ///
    /// @brief
    ///     Sets orientation.
    ///
    void SetOrientation(Orientation value);

    ///
    /// @brief
    ///     Gets default value.
    ///
    float32_t GetDefaultValue() const;

    ///
    /// @brief
    ///     Sets default value.
    ///
    void SetDefaultValue(float32_t value);

public:
    ///
    /// @brief
    ///     Increments range by specified amount.
    ///
    /// @param[in] is_small
    ///     A value indicating increment value.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool Increment(bool is_small = true);

    ///
    /// @brief
    ///     Decrements range by specified amount.
    ///
    /// @param[in] is_small
    ///     A value indicating decrement value.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool Decrement(bool is_small = true);

public:
    virtual bool Deserialize(Xml::XmlNode* node) override;
};
//------------------------------------------------------------------------------------------------//
inline float32_t RangeBase::GetRangeMin() const
{
    return _range_min;
}
//------------------------------------------------------------------------------------------------//
inline void RangeBase::SetRangeMin(float32_t value)
{
    _range_min = value;
    OnPropertyChanged(Core::StrongName("RangeMin"));
}
//------------------------------------------------------------------------------------------------//
inline float32_t RangeBase::GetRangeMax() const
{
    return _range_max;
}
//------------------------------------------------------------------------------------------------//
inline void RangeBase::SetRangeMax(float32_t value)
{
    _range_max = value;
    OnPropertyChanged(Core::StrongName("RangeMax"));
}
//------------------------------------------------------------------------------------------------//
inline float32_t RangeBase::GetSmallStepValue() const
{
    return _range_small_step;
}
//------------------------------------------------------------------------------------------------//
inline void RangeBase::SetSmallStepValue(float32_t value)
{
    _range_small_step = value;
    OnPropertyChanged(Core::StrongName("SmallStep"));
}
//------------------------------------------------------------------------------------------------//
inline float32_t RangeBase::GetLargeStepValue() const
{
    return _range_large_step;
}
//------------------------------------------------------------------------------------------------//
inline void RangeBase::SetLargeStepValue(float32_t value)
{
    _range_large_step = value;
    OnPropertyChanged(Core::StrongName("LargeStep"));
}
//------------------------------------------------------------------------------------------------//
inline float32_t RangeBase::GetValue() const
{
    return _value;
}
//------------------------------------------------------------------------------------------------//
inline void RangeBase::SetValue(float32_t value)
{
    _value = std::min(std::max(value, _range_min), _range_max);

    if (_event_handler != nullptr)
    {
        _event_handler->OnValueChanged(this);
        OnPropertyChanged(Core::StrongName("Value"));
    }
}
//------------------------------------------------------------------------------------------------//
inline void RangeBase::ResetValue()
{
    SetValue(_default_value);
}
//------------------------------------------------------------------------------------------------//
inline float32_t RangeBase::GetPercentage() const
{
    return (_value - _range_min) / (_range_max - _range_min);
}
//------------------------------------------------------------------------------------------------//
inline Orientation RangeBase::GetOrientation() const
{
    return _orientation;
}
//------------------------------------------------------------------------------------------------//
inline void RangeBase::SetOrientation(Orientation value)
{
    _orientation = value;
    OnPropertyChanged(Core::StrongName("Orientation"));
}
//------------------------------------------------------------------------------------------------//
inline float32_t RangeBase::GetDefaultValue() const
{
    return _default_value;
}
//------------------------------------------------------------------------------------------------//
inline void RangeBase::SetDefaultValue(float32_t value)
{
    _default_value = value;
    OnPropertyChanged(Core::StrongName("DefaultValue"));
}
//------------------------------------------------------------------------------------------------//
}
}
}
}
//------------------------------------------------------------------------------------------------//
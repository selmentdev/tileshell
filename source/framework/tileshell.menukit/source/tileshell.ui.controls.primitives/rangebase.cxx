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
#include <tileshell.ui.controls.primitives/rangebase.hxx>

namespace TileShell::UI::Controls::Primitives
{

    RangeBase::RangeBase()
        : _range_min(0.0F)
        , _range_max(1.0F)
        , _range_small_step(0.05F)
        , _range_large_step(0.1F)
        , _value(0.0F)
        , _orientation(Orientation::Horizontal)
    {
    }

    RangeBase::~RangeBase()
    {
    }

    bool RangeBase::Deserialize(Xml::XmlNode* node)
    {
        if (Control::Deserialize(node) == false)
        {
            return false;
        }

        using namespace Serialization;

        FloatValueSerializer::Deserialize(_range_min, node->first_attribute("RangeMin"));
        FloatValueSerializer::Deserialize(_range_max, node->first_attribute("RangeMax"));
        FloatValueSerializer::Deserialize(_range_small_step, node->first_attribute("RangeSmallStep"));
        FloatValueSerializer::Deserialize(_range_large_step, node->first_attribute("RangeLargeStep"));

        if (!FloatValueSerializer::Deserialize(_default_value, node->first_attribute("DefaultValue")))
        {
            _default_value = _range_min;
        }

        if (!FloatValueSerializer::Deserialize(_value, node->first_attribute("Value")))
        {
            _value = _default_value;
        }

        ValueSerializer<Orientation>::Deserialize(_orientation, node->first_attribute("Orientation"));

        return true;
    }

    bool RangeBase::Increment(bool small)
    {
        if (small == true)
        {
            SetValue(GetValue() + _range_small_step);
        }
        else
        {
            SetValue(GetValue() + _range_large_step);
        }

        return true;
    }

    bool RangeBase::Decrement(bool small)
    {
        if (small == true)
        {
            SetValue(GetValue() - _range_small_step);
        }
        else
        {
            SetValue(GetValue() - _range_large_step);
        }

        return true;
    }

}

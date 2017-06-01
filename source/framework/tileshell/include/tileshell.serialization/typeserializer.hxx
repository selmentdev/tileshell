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
#ifndef _TileShell_Serialization_H__
#define _TileShell_Serialization_H__

#include <tileshell/required.hxx>
#include <tileshell.core/types.hxx>
#include <tileshell.core/strongname.hxx>
#include <tileshell.drawing/thickness.hxx>
#include <tileshell.drawing/rect.hxx>
#include <tileshell.drawing/size.hxx>
#include <tileshell.drawing/point.hxx>
#include <tileshell.drawing/transform.hxx>
#include <tileshell.drawing/color.hxx>
#include <tileshell.xml/xml.hxx>

namespace TileShell::Serialization
{

    template <typename T>
    struct ValueSerializer
    {
        static bool Deserialize(T& out_result, const Xml::XmlAttribute* attr)
        {
            return false;
        }
    };

    struct ThicknessValueSerializer
    {
        static bool Deserialize(Drawing::Thickness& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            Drawing::Thickness result;
            bool valid = ::sscanf_s(attr->value(), "%f,%f,%f,%f", &result.Left, &result.Top, &result.Right,
                &result.Bottom) == 4;

            if (valid)
            {
                out_result = result;
            }

            return valid;
        }
    };

    struct PointValueSerializer
    {
        static bool Deserialize(Drawing::Point& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            Drawing::Point result;
            bool valid = ::sscanf_s(attr->value(), "%f,%f", &result.X, &result.Y) == 2;

            if (valid)
            {
                out_result = result;
            }

            return valid;
        }
    };

    struct RectValueSerializer
    {
        static bool Deserialize(Drawing::Rect& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            Drawing::Rect result;
            bool valid = ::sscanf_s(attr->value(), "%f,%f,%f,%f", &result.X, &result.Y, &result.Width,
                &result.Height) == 4;

            if (valid)
            {
                out_result = result;
            }

            return valid;
        }
    };

    struct SizeValueSerializer
    {
        static bool Deserialize(Drawing::Size& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            Drawing::Size result;
            bool valid = ::sscanf_s(attr->value(), "%f,%f", &result.Width, &result.Height) == 2;

            if (valid)
            {
                out_result = result;
            }

            return valid;
        }
    };

    struct ScaleTransformValueSerializer
    {
        static bool Deserialize(Drawing::ScaleTransform& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            Drawing::ScaleTransform result;
            bool valid = ::sscanf_s(attr->value(), "%f,%f", &result.ScaleX, &result.ScaleY) == 2;

            if (valid)
            {
                out_result = result;
            }

            return valid;
        }
    };

    struct SkewTransformValueSerializer
    {
        static bool Deserialize(Drawing::SkewTransform& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            Drawing::SkewTransform result;
            bool valid = ::sscanf_s(attr->value(), "%f,%f", &result.AngleX, &result.AngleY) == 2;

            if (valid)
            {
                out_result = result;
            }

            return valid;
        }
    };

    struct TranslateTransformValueSerializer
    {
        static bool Deserialize(Drawing::TranslateTransform& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            Drawing::TranslateTransform result;
            bool valid = ::sscanf_s(attr->value(), "%f,%f", &result.X, &result.Y) == 2;

            if (valid)
            {
                out_result = result;
            }

            return valid;
        }
    };

    struct RotateTransformValueSerializer
    {
        static bool Deserialize(Drawing::RotateTransform& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            Drawing::RotateTransform result;
            bool valid = ::sscanf_s(attr->value(), "%f", &result.Angle) == 1;

            if (valid)
            {
                out_result = result;
            }

            return valid;
        }
    };

    struct TransformValueSerializer
    {
        static bool Deserialize(Drawing::Transform& out_result, const Xml::XmlNode* node)
        {
            if (node == nullptr)
            {
                return false;
            }

            TranslateTransformValueSerializer::Deserialize(out_result.Translate, node->first_attribute("Translate"));
            RotateTransformValueSerializer::Deserialize(out_result.Rotate, node->first_attribute("Rotate"));
            ScaleTransformValueSerializer::Deserialize(out_result.Scale, node->first_attribute("Scale"));
            SkewTransformValueSerializer::Deserialize(out_result.Skew, node->first_attribute("Skew"));

            return true;
        }
    };

    struct StringValueSerializer
    {
        static bool Deserialize(string_t& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            out_result.assign(attr->value());

            return true;
        }
    };

    struct FloatValueSerializer
    {
        static bool Deserialize(float32_t& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            return ::sscanf_s(attr->value(), "%f", &out_result) == 1;
        }
    };

    struct Int16ValueSerializer
    {
        static bool Deserialize(int16_t& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            int result;

            if (::sscanf_s(attr->value(), "%d", &result) == 1)
            {
                out_result = static_cast<int16_t>(result);
                return true;
            }

            return false;
        }
    };

    struct Int32ValueSerializer
    {
        static bool Deserialize(int32_t& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            int result;

            if (::sscanf_s(attr->value(), "%d", &result) == 1)
            {
                out_result = result;
                return true;
            }

            return false;
        }
    };

    struct UInt16ValueSerializer
    {
        static bool Deserialize(uint16_t& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            unsigned int result;

            if (::sscanf_s(attr->value(), "%d", &result) == 1)
            {
                out_result = static_cast<uint16_t>(result);
                return true;
            }

            return false;
        }
    };

    struct CharValueSerializer
    {
        static bool Deserialize(char& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            if (attr->value() != nullptr)
            {
                out_result = attr->value()[0];
                return true;
            }

            return false;
        }
    };

    struct StrongNameValueSerializer
    {
        static bool Deserialize(Core::StrongName& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            out_result = Core::StrongName::Create(attr->value());

            return true;
        }
    };

    struct BoolValueSerializer
    {
        static bool Deserialize(bool& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            if (attr->value() != nullptr)
            {
                bool is_true = _strnicmp(attr->value(), "true", 5) == 0;
                bool is_one = _strnicmp(attr->value(), "1", 2) == 0;
                out_result = is_one || is_true;
                return true;
            }

            return false;
        }
    };

    struct Float32x3ValueSerializer
    {
        static bool Deserialize(float32x3_t& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            float32x3_t result;
            bool valid = ::sscanf_s(attr->value(), "%f,%f,%f", &result.X, &result.Y, &result.Z) == 3;

            if (valid)
            {
                out_result = result;
            }

            return valid;

        }
    };

    struct ColorValueSerializer
    {
        static bool Deserialize(Drawing::Color& out_result, const Xml::XmlAttribute* attr)
        {
            if (attr == nullptr)
            {
                return false;
            }

            float32x4_t result;
            bool valid = ::sscanf_s(attr->value(), "%f,%f,%f,%f", &result.X, &result.Y, &result.Z,
                &result.W) == 4;

            if (valid)
            {
                out_result = Drawing::Color(
                    result.X,
                    result.Y,
                    result.Z,
                    result.W);
            }

            return valid;
        }
    };

}
#endif /* _TileShell_Serialization_H__ */
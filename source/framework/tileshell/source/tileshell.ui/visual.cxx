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
#include <tileshell.ui/visual.hxx>
#include <tileshell.serialization/typeserializer.hxx>
#include <tileshell.drawing/matrix.hxx>
#include <tileshell.drawing/color.hxx>
#include <tileshell.drawing/font.hxx>

namespace TileShell::UI
{

    Visual::Visual()
        : _transform()
        , _local_transform_matrix()
        , _rectangle(0.0F)
        , _padding(0.0F)
        , _style()
        , _name()
        , _opacity(1.0F)
        , _visibility(true)
    {
    }

    Visual::~Visual()
    {
    }

    bool Visual::Deserialize(Xml::XmlNode* node)
    {
        if (node == nullptr)
        {
            return false;
        }

        using namespace TileShell::Serialization;

        //
        // Transform (optional)
        //
        TransformValueSerializer::Deserialize(_transform, node);

        //
        // Rectangle
        //
        RectValueSerializer::Deserialize(_rectangle, node->first_attribute("Rectangle"));

        //
        // Padding (optional)
        //
        ThicknessValueSerializer::Deserialize(_padding, node->first_attribute("Padding"));

        //
        // Opacity (optional)
        //
        FloatValueSerializer::Deserialize(_opacity, node->first_attribute("Opacity"));

        //
        // Visibility (optional)
        //
        BoolValueSerializer::Deserialize(_visibility, node->first_attribute("Visibility"));

        //
        // Name (required)
        //
        if (StrongNameValueSerializer::Deserialize(_name, node->first_attribute("Name")) == false)
        {
            return false;
        }

        //
        // Update transform matrix.
        //
        _transform.ComputeTransformMatrix(_local_transform_matrix, _rectangle);

        return true;
    }

    bool Visual::OnPropertyChanged(const Core::StrongName& property_name)
    {
        if (property_name == Core::StrongName("Transform"))
        {
            _transform.ComputeTransformMatrix(_local_transform_matrix, _rectangle);
            return true;
        }

        return true;
    }

}

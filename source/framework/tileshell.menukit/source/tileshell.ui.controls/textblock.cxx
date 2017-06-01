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
#include <tileshell.ui.controls/textblock.hxx>

namespace TileShell::UI::Controls
{

    TextBlock::TextBlock()
        : Primitives::TextBase()
        , _styleitem_background()
        , _styleitem_name()
    {
        _is_focusable = false;
    }

    TextBlock::~TextBlock()
    {
    }

    bool TextBlock::Deserialize(Xml::XmlNode* node)
    {
        if (Primitives::TextBase::Deserialize(node) == false)
        {
            return false;
        }

        Serialization::StrongNameValueSerializer::Deserialize(_styleitem_name,
            node->first_attribute("StyleItem"));
        OnPropertyChanged(Core::StrongName("StyleItem"));

        Serialization::ColorValueSerializer::Deserialize(_background_color,
            node->first_attribute("BackgroundColor"));
        OnPropertyChanged(Core::StrongName("BackgroundColor"));

        return true;
    }

    bool TextBlock::Update(float32_t delta)
    {
        return Primitives::TextBase::Update(delta);
    }

    bool TextBlock::OnPropertyChanged(const Core::StrongName& property_name)
    {
        if (!TextBase::OnPropertyChanged(property_name))
        {
            return false;
        }

        if (property_name == Core::StrongName("StyleItem"))
        {
            GetStyle()->GetItem(
                _styleitem_background,
                _styleitem_name);
        }

        return true;
    }

    bool TextBlock::GenerateGeometry(Drawing::GeometryBuilder& builder, GeometryType geometry_type)
    {
        if (geometry_type == GeometryType::Dynamic)
        {
            if (_styleitem_name != Core::StrongName::Empty())
            {
                builder.DrawStyleItem(
                    _global_transform_matrix,
                    _background_color,
                    _global_zorder,
                    _rectangle, _padding,
                    _styleitem_background);
            }
        }
        else if (geometry_type == GeometryType::StaticText)
        {
            builder.DrawString(
                _global_transform_matrix,
                _text_color,
                _global_zorder,
                _rectangle,
                GetStyle()->GetFont(),
                _text.c_str(),
                _font_size,
                _text_align);
        }

        return true;
    }

    bool TextBlock::OnKeyDown(const Input::KeyEventArgs& e)
    {
        return Primitives::TextBase::OnKeyDown(e);
    }

    bool TextBlock::OnKeyUp(const Input::KeyEventArgs& e)
    {
        return Primitives::TextBase::OnKeyUp(e);
    }

    bool TextBlock::OnMouseDown(const Input::MouseEventArgs& e)
    {
        return Primitives::TextBase::OnMouseDown(e);
    }

    bool TextBlock::OnMouseUp(const Input::MouseEventArgs& e)
    {
        return Primitives::TextBase::OnMouseUp(e);
    }

    bool TextBlock::OnMouseMove(const Input::MouseEventArgs& e)
    {
        return Primitives::TextBase::OnMouseMove(e);
    }

}

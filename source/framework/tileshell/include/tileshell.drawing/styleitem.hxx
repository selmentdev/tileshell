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
#ifndef _TileShell_Render_StyleItem_H__
#define _TileShell_Render_StyleItem_H__

#include <tileshell.drawing/rect.hxx>
#include <tileshell.drawing/thickness.hxx>
#include <tileshell.xml/xml.hxx>
#include <tileshell.serialization/typeserializer.hxx>

namespace TileShell::Drawing
{
    ///
    /// @remarks
    ///     This structure defines 1 quad texture coordinates. This structure is simpler version of
    ///     Theme9Grid structure, which is more specialized.
    ///
    /// @note
    ///     Xml format:
    ///
    struct StyleItem1Quad
    {
        ///
        /// Contains texture coordinates.
        ///
        Drawing::Rect   Rectangle;
    };

    ///
    /// 9Grid.
    ///
    /// @remarks
    ///     This structure defines 9 grid texture coordinates. The Border contains outer box
    ///     texture coordinates, and the InnerBox contains inner box texture coordinates relative
    ///     padding values.
    ///
    /// @note
    ///     Xml format:
    ///
    struct StyleItem9Grid
    {
        ///
        /// Contains texture coordinates.
        ///
        Rect        Rectangle;

        ///
        /// Contains center cell texture coordinates padding.
        ///
        Thickness   Padding;
    };

}

namespace TileShell::Serialization
{

    struct StyleItem1QuadValueSerializer
    {
        static bool Deserialize(Drawing::StyleItem1Quad& out_result, const Xml::XmlNode* node)
        {
            return RectValueSerializer::Deserialize(out_result.Rectangle, node->first_attribute("Rectangle"));
        }
    };

    struct StyleItem9GridValueSerializer
    {
        static bool Deserialize(Drawing::StyleItem9Grid& out_result, const Xml::XmlNode* node)
        {
            return RectValueSerializer::Deserialize(out_result.Rectangle, node->first_attribute("Rectangle")) &&
                ThicknessValueSerializer::Deserialize(out_result.Padding, node->first_attribute("Padding"));
        }
    };

}

#endif /* _TileShell_Render_StyleItem_H__ */
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
#ifndef _TileShell_Render_Theme_H__
#define _TileShell_Render_Theme_H__
//------------------------------------------------------------------------------------------------//
#include <tileshell.core/reference.hxx>
#include <tileshell.core/referenced.hxx>
#include <tileshell.serialization/typeserializer.hxx>
#include <tileshell.drawing/texture.hxx>
#include <tileshell.drawing/styleitem.hxx>
#include <tileshell.drawing/font.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
// Forward declarations
class StyleManager;

typedef std::map<Core::StrongName, StyleItem1Quad, std::less<Core::StrongName>, Core::StlAllocator<std::pair<const Core::StrongName, StyleItem1Quad>>>
StyleItem1QuadCollection;
typedef std::map<Core::StrongName, StyleItem9Grid, std::less<Core::StrongName>, Core::StlAllocator<std::pair<const Core::StrongName, StyleItem9Grid>>>
StyleItem9GridCollection;


///
/// @brief
///     This class represents single theme.
///
/// @remarks
///     Theme stores objects like 9grid and 1quad, that may be applied to running UIElements.
///
class Style
    : public Core::Referenced
    , public Core::Allocator<Style>
{
    friend class StyleManager;

private:
    TextureRef                  _style_texture;
    StyleItem9GridCollection    _style_9grid_collection;
    StyleItem1QuadCollection    _style_1quad_collection;
    FontRef                     _style_font;

private:
    ///
    /// Creates instance of the Style class.
    ///
    Style();

    ///
    /// Destroys instance of the Style class.
    ///
    virtual ~Style();

public:
    ///
    /// @brief
    ///     Deserializes instance of the Style class from xml node.
    ///
    /// @param[in] node
    ///     A source xml node.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool Deserialize(Xml::XmlNode* node);

    ///
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool Load(const string_t& name);

public:
    ///
    /// @brief
    ///     Gets texture assigned to style.
    ///
    const TextureRef& GetTexture() const;

    ///
    /// @brief
    ///     Sets texture assigned to style.
    ///
    void SetTexture(const TextureRef& value);

    ///
    /// @brief
    ///     Gets font assigned to style.
    ///
    const FontRef& GetFont() const;

    ///
    /// @brief
    ///     Sets font assigned to style
    ///
    void SetFont(const FontRef& value);

    ///
    /// Gets item definition.
    ///
    /// @param[out] out_result
    ///     A target theme item data.
    /// @param[in] name
    ///     A name of the item.
    ///
    /// @note
    ///     @c out_result receives item when available.
    ///
    bool GetItem(StyleItem1Quad& out_result, const Core::StrongName& name) const;

    ///
    /// Gets item definition.
    ///
    /// @param[out] out_result
    ///     A target theme item data.
    /// @param[in] name
    ///     A name of the item.
    ///
    /// @note
    ///     @c out_result receives item when available.
    ///
    bool GetItem(StyleItem9Grid& out_result, const Core::StrongName& name) const;
};
typedef Core::Reference<Style> StyleRef;
//------------------------------------------------------------------------------------------------//
inline const TextureRef& Style::GetTexture() const
{
    return _style_texture;
}
//------------------------------------------------------------------------------------------------//
inline void Style::SetTexture(const TextureRef& value)
{
    _style_texture = value;
}
//------------------------------------------------------------------------------------------------//
inline const FontRef& Style::GetFont() const
{
    return _style_font;
}
//------------------------------------------------------------------------------------------------//
inline void Style::SetFont(const FontRef& value)
{
    _style_font = value;
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Render_Theme_H__ */
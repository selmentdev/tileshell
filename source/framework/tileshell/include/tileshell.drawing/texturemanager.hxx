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
#ifndef _TileShell_Render_TextureManager_H__
#define _TileShell_Render_TextureManager_H__
//------------------------------------------------------------------------------------------------//
#include <tileshell.core/types.hxx>
#include <tileshell.core/reference.hxx>
#include <tileshell.core/referenced.hxx>
#include <tileshell/externalresourcefactory.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
class Texture;
typedef Core::Reference<Texture> TextureRef;

///
/// This class implements texture management.
///
class TextureManager
{
private:
    typedef std::map<string_t, TextureRef> TextureCollection;

private:
    static TextureCollection            _texture_collection;

public:
    ///
    /// Initializes texture manager.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    static bool Initialize();

    ///
    /// Shutdowns texture manager.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    static bool Shutdown();

public:
    ///
    /// Gets texture for the specified name.
    ///
    /// @param[in] name
    ///     A texture name to load or create.
    ///
    static TextureRef GetTexture(const string_t& name);

    ///
    /// Releases texture from manager.
    ///
    /// @note
    ///     If there is any reference to this texture outside texture manager, texture object
    ///     is destroyed when last reference is released.
    ///
    /// @param[in] texture
    ///     A texture to release.
    ///
    static void ReleaseTexture(TextureRef texture);
};

}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Render_TextureManager_H__ */
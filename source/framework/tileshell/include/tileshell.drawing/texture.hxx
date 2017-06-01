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
#ifndef _TileShell_Render_Texture_H__
#define _TileShell_Render_Texture_H__

#include <tileshell/required.hxx>
#include <tileshell.core/referenced.hxx>
#include <tileshell.core/reference.hxx>
#include <tileshell.drawing/size.hxx>
#include <tileshell.drawing/rect.hxx>

namespace TileShell::Drawing
{
    ///
    /// This class represents texture resource.
    ///
    class Texture : public Core::Referenced
    {
    public:
        ///
        /// Destroys instance of the Texture class.
        ///
        virtual ~Texture() {}

        ///
        /// Gets size of the texture in texels.
        ///
        virtual Size GetSize() = 0;

        ///
        /// Gets rectagnel of the texture in texels.
        ///
        Rect GetRectangle();
    };
    typedef Core::Reference<Texture> TextureRef;

    inline Rect Texture::GetRectangle()
    {
        Size size = GetSize();
        return Rect(0.0F, 0.0F, size.Width, size.Height);
    }

}

#endif /* _TileShell_Render_Texture_H__ */
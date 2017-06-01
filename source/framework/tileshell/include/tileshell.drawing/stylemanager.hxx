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
#ifndef _TileShell_Render_ThemeManager_H__
#define _TileShell_Render_ThemeManager_H__

#include <tileshell.core/types.hxx>
#include <tileshell.core/reference.hxx>
#include <tileshell.core/referenced.hxx>
#include <tileshell.drawing/style.hxx>
#include <tileshell/externalresourcefactory.hxx>

namespace TileShell::Drawing
{

    ///
    /// This class implements texture manager.
    ///
    class StyleManager
    {
    private:
        typedef std::map<string_t, StyleRef> StyleCollection;

    private:
        static StyleCollection              _style_collection;

    public:
        ///
        /// Initializes theme manager.
        ///
        /// @returns
        ///     true when successful, false otherwise.
        ///
        static bool Initialize();

        ///
        /// Shutdowns theme manager.
        ///
        /// @returns
        ///     true when successful, false otherwise.
        ///
        static bool Shutdown();

    public:
        ///
        /// Gets theme for specified name.
        ///
        /// @param[in] name
        ///     A theme name to load or create.
        ///
        static StyleRef GetStyle(const string_t& name);
    };
}

#endif /* _TileShell_Render_ThemeManager_H__ */
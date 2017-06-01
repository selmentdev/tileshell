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
#ifndef _TileShell_Render_ResourceFactory_H__
#define _TileShell_Render_ResourceFactory_H__

#include <tileshell/externalresourcefactory.hxx>

namespace TileShell::Drawing
{

    ///
    /// @brief
    ///     Resource factory public interface.
    ///
    /// @details
    ///     This class provides access to external resource factory.
    ///
    class ResourceFactory
    {
    private:
        static ExternalResourceFactory* _resource_factory;

    public:
        ///
        /// @brief
        ///     Initializes resource factory using external resource factory.
        ///
        /// @param[in] resource_factory
        ///     An external resource factory.
        ///
        /// @returns
        ///     true when successful, false otherwise.
        ///
        static bool Initialize(ExternalResourceFactory* resource_factory);

        ///
        /// @brief
        ///     Shutdowns resource factory.
        ///
        /// @remarks
        ///     After shutdown resource factory is inaccessible and resource creation methods always
        ///     returns nullptr.
        ///
        /// @returns
        ///     true when successful, false otherwise.
        ///
        static bool Shutdown();

    public:
        ///
        /// @brief
        ///     Creates texture resource from specified path.
        ///
        /// @param[in] path
        ///     A path to texture.
        ///
        /// @returns
        ///     The reference to newly created texture.
        ///
        /// @remarks
        ///     Engine can provide video texture using this method.
        ///
        static TextureRef CreateTexture(const string_t& path);

        ///
        /// @brief
        ///     Creates new geometry buffer.
        ///
        /// @returns
        ///     The reference to newly created geometry buffer.
        static GeometryBufferRef CreateGeometryBuffer();
    };

}

#endif /* _TileShell_Render_ResourceFactory_H__ */
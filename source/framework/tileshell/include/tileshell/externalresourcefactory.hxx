#pragma once
#ifndef _TileShell_ExternalResourceFactory_H__
#define _TileShell_ExternalResourceFactory_H__

#include <tileshell/required.hxx>
#include <tileshell.core/reference.hxx>
#include <tileshell.core/referenced.hxx>
#include <tileshell.drawing/texture.hxx>
#include <tileshell.drawing/geometrybuffer.hxx>

namespace TileShell
{
    class ExternalResourceFactory
    {
    protected:
        virtual ~ExternalResourceFactory() { }
    public:
        ///
        /// Initializes factory.
        ///
        /// @returns
        ///     true when successful, false otherwise.
        ///
        virtual bool Initialize() = 0;

        ///
        /// Shutdowns factory.
        ///
        /// @returns
        ///     true when successful, false otherwise.
        ///
        virtual bool Shutdown() = 0;

    public:
        ///
        /// Creates texture resource for specified path.
        ///
        /// @param[in] path
        ///     A path to texture.
        ///
        /// @returns
        ///     The reference to the texture, nullptr when failed.
        ///
        virtual Drawing::TextureRef CreateTexture(const string_t& path) = 0;

        ///
        /// Creates geometry buffer.
        ///
        /// @returns
        ///     The reference to the geometry buffer, nullptr, when failed.
        ///
        virtual Drawing::GeometryBufferRef CreateGeometryBuffer() = 0;
    };

}

#endif /* _TileShell_ExternalResourceFactory_H__ */
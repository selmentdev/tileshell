#ifndef INCLUDED_CORE_RENDERING_MESHRENDERER_HXX
#define INCLUDED_CORE_RENDERING_MESHRENDERER_HXX

//
// Copyright (C) Selmentdev, 2017
//
//      See LICENSE file in the project root for full license information.
//

#include <core/common.hxx>
#include <core/reference.hxx>
#include <core.rendering/buffers.hxx>
#include <core.rendering/commandlist.hxx>

namespace Core::Rendering
{
    using MeshRendererRef = Reference<class MeshRenderer>;
    class MeshRenderer : public Object
    {
    private:
        Core::Rendering::VertexBufferRef m_VertexBuffer;
        Core::Rendering::IndexBufferRef m_IndexBuffer;

    public:
        MeshRenderer() noexcept;
        virtual ~MeshRenderer() noexcept;

    public:
        void Bind(const Rendering::CommandListRef& commandList) noexcept;
        void Render(const Rendering::CommandListRef& commandList) noexcept;
    };
}

#endif // INCLUDED_CORE_RENDERING_MESHRENDERER_HXX
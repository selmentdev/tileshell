//
// Copyright (C) Selmentdev, 2017
//
//      See LICENSE file in the project root for full license information.
//

#include <core.rendering/buffers.hxx>
#include <core.rendering/rendersystem.hxx>

namespace Core::Rendering
{
    IndexBuffer::IndexBuffer(RenderSystem* renderSystem, const BufferDesc& desc) noexcept
        : m_RenderSystem{ renderSystem }
        , m_Buffer{}
    {
        auto device = this->m_RenderSystem->m_Device;

        //
        // Just immutable buffer.
        //
        D3D11_BUFFER_DESC sd{};
        sd.Usage = D3D11_USAGE_IMMUTABLE;
        sd.ByteWidth = static_cast<::UINT>(desc.Size);
        sd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        sd.CPUAccessFlags = 0;
        sd.MiscFlags = 0;

        //
        // Prepare data.
        //
        D3D11_SUBRESOURCE_DATA sr{};
        sr.pSysMem = desc.Pointer;

        //
        // And create buffer.
        //
        DX::Ensure(device->CreateBuffer(&sd, &sr, m_Buffer.GetAddressOf()));
    }

    IndexBuffer::~IndexBuffer() noexcept
    {
    }
}
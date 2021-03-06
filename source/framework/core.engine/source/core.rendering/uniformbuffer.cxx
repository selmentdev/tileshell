//
// Copyright (C) Selmentdev, 2017
//
//      See LICENSE file in the project root for full license information.
//

#include <core.rendering/buffers.hxx>
#include <core.rendering/rendersystem.hxx>

namespace Core::Rendering
{
    UniformBuffer::UniformBuffer(RenderSystem* renderSystem, const BufferDesc& desc) noexcept
        : m_RenderSystem{ renderSystem }
        , m_Buffer{}
    {
        auto device = m_RenderSystem->m_Device;

        //
        // Standard dynamic constant bufer.
        //
        D3D11_BUFFER_DESC sd{};
        sd.Usage = D3D11_USAGE_DYNAMIC;
        sd.ByteWidth = static_cast<::UINT>(desc.Size);
        sd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        sd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        sd.MiscFlags = 0;

        //
        // Setup initial data.
        //
        D3D11_SUBRESOURCE_DATA sr{};
        sr.pSysMem = desc.Pointer;

        //
        // Create buffer.
        //
        DX::Ensure(device->CreateBuffer(&sd, &sr, m_Buffer.GetAddressOf()));
    }

    UniformBuffer::~UniformBuffer() noexcept
    {
    }
}
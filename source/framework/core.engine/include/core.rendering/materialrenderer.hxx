#ifndef INCLUDED_CORE_RENDERING_MATERIALRENDERER_HXX
#define INCLUDED_CORE_RENDERING_MATERIALRENDERER_HXX

//
// Copyright (C) Selmentdev, 2017
//
//      See LICENSE file in the project root for full license information.
//

#include <core/common.hxx>
#include <core/reference.hxx>
#include <core.rendering/common.hxx>
#include <core.rendering/buffers.hxx>
#include <core.rendering/commandlist.hxx>
#include <core.rendering/graphicspipelinestate.hxx>
#include <DirectXColors.h>

namespace Core::Rendering
{
    using MaterialRendererRef = Reference<class MaterialRenderer>;
    class MaterialRenderer : public Object
    {
    public:
        struct ShaderParams
        {
            DirectX::XMFLOAT4A Color;
        };
    private:
        ShaderParams m_ShaderParams;
        UniformBufferRef m_ShaderParamsBuffer;
        GraphicsPipelineStateRef m_PipelineState;
        SamplerRef m_TextureSampler;
        Texture2DRef m_Texture;

    public:
        MaterialRenderer(const std::string& pixelShader, const std::string& vertexShader) noexcept;
        virtual ~MaterialRenderer() noexcept;

    public:
        void Bind(const Core::Rendering::CommandListRef& commandList) noexcept;

    public:
        ShaderParams& GetMaterialData() noexcept
        {
            return m_ShaderParams;
        }

        void XM_CALLCONV SetDiffuseColor(DirectX::FXMVECTOR value) noexcept
        {
            DirectX::XMStoreFloat4A(&m_ShaderParams.Color, value);
        }

        void SetTextureSampler(const SamplerRef& sampler) noexcept
        {
            m_TextureSampler = sampler;
        }

        void SetTexture(const Texture2DRef& texture) noexcept
        {
            m_Texture = texture;
        }
    };
}

#endif // INCLUDED_CORE_RENDERING_MATERIALRENDERER_HXX
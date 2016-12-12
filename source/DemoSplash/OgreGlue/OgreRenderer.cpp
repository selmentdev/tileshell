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
#include "../OgreGlue/OgreRenderer.h"
#include "../OgreGlue/OgreTexture.h"
#include "../OgreGlue/OgreVertexBuffer.h"
//------------------------------------------------------------------------------------------------//
namespace OgreGlue
{
//------------------------------------------------------------------------------------------------//
OgreRenderer::OgreRenderer()
    : _scene(nullptr)
    , _render_system(nullptr)
    , _color_blend_mode()
    , _alpha_blend_mode()
    , _texture_address_mode()
    , _draw_calls(0)
    , _vertices_count(0)
    , _scale(1.0F)
    , _world_matrix()
    , _wireframe(false)
{
    _color_blend_mode.blendType     = Ogre::LBT_COLOUR;
    _color_blend_mode.source1       = Ogre::LBS_TEXTURE;
    _color_blend_mode.source2       = Ogre::LBS_DIFFUSE;
    _color_blend_mode.operation     = Ogre::LBX_MODULATE;

    _alpha_blend_mode.blendType     = Ogre::LBT_ALPHA;
    _alpha_blend_mode.source1       = Ogre::LBS_CURRENT;
    _alpha_blend_mode.source2       = Ogre::LBS_TEXTURE;
    _alpha_blend_mode.operation     = Ogre::LBX_BLEND_TEXTURE_ALPHA;

    _texture_address_mode.u         = Ogre::TextureUnitState::TAM_CLAMP;
    _texture_address_mode.v         = Ogre::TextureUnitState::TAM_CLAMP;
    _texture_address_mode.w         = Ogre::TextureUnitState::TAM_CLAMP;
}
//------------------------------------------------------------------------------------------------//
OgreRenderer::~OgreRenderer()
{
}
//------------------------------------------------------------------------------------------------//
void OgreRenderer::renderQueueStarted(Ogre::uint8 queue_group_id, const Ogre::String& invocation,
                                      bool& skipThisInvocation)
{
    if (queue_group_id != Ogre::RENDER_QUEUE_OVERLAY)
    {
        return;
    }

    if (_scene != nullptr)
    {
        _render_system                  = Ogre::Root::getSingletonPtr()->getRenderSystem();

        BeginRender();
        _draw_calls = 0;
        _scene->Draw(this);
        EndRender();
    }
}
//------------------------------------------------------------------------------------------------//
void OgreRenderer::renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation,
                                    bool& repeatThisInvocation)
{
}
//------------------------------------------------------------------------------------------------//
/*void OgreRenderer::DoRender(const TileShell::Drawing::Matrix4x4& world_matrix, TileShell::Drawing::GeometryBufferRef gbuffer, TileShell::Drawing::TextureRef texture, size_t vertex_count)
{
    Ogre::Matrix4 wm(
            world_matrix._11, world_matrix._12, world_matrix._13, world_matrix._14,
            world_matrix._21, world_matrix._22, world_matrix._23, world_matrix._24,
            world_matrix._31, world_matrix._32, world_matrix._33, world_matrix._34,
            world_matrix._41, world_matrix._42, world_matrix._43, world_matrix._44);
    wm = wm.transpose();

    _render_system->_setWorldMatrix(wm);

    if (texture != nullptr)
    {
        OgreGlue::OgreTexture* ogre_texture = texture.cast<OgreGlue::OgreTexture>();

        Ogre::TexturePtr ogre_texture_ptr = ogre_texture->GetTexture();

        if (!ogre_texture_ptr.isNull())
        {
            _render_system->_setTexture(0, true, ogre_texture_ptr);
            _render_system->_setTextureUnitFiltering(0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_NONE);
        }
    }

    OgreGlue::OgreVertexBuffer* vertex_buffer = gbuffer.cast<OgreGlue::OgreVertexBuffer>();
    Ogre::RenderOperation* rop = vertex_buffer->GetRenderOperation();
    rop->vertexData->vertexCount = vertex_count;

    _render_system->_render(*rop);
    ++_draw_calls;
}*/
//------------------------------------------------------------------------------------------------//
void OgreRenderer::DoRender(
    TileShell::Drawing::GeometryBufferRef gbuffer,
    TileShell::Drawing::TextureRef texture, size_t vertex_count)
{
    _render_system->_setWorldMatrix(_world_matrix);

    if (texture != nullptr)
    {
        OgreGlue::OgreTexture* ogre_texture = texture.cast<OgreGlue::OgreTexture>();

        Ogre::TexturePtr ogre_texture_ptr = ogre_texture->GetTexture();

        if (!ogre_texture_ptr.isNull())
        {
            _render_system->_setTexture(0, true, ogre_texture_ptr);
            _render_system->_setTextureUnitFiltering(0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_NONE);
        }
    }

    OgreGlue::OgreVertexBuffer* vertex_buffer = gbuffer.cast<OgreGlue::OgreVertexBuffer>();
    Ogre::RenderOperation* rop = vertex_buffer->GetRenderOperation();
    rop->vertexData->vertexCount = vertex_count;

    _render_system->_render(*rop);
    ++_draw_calls;
    _vertices_count += vertex_count;
}
//------------------------------------------------------------------------------------------------//
void OgreRenderer::DoRenderScreen(
    TileShell::Drawing::GeometryBufferRef gbuffer,
    TileShell::Drawing::TextureRef texture, size_t vertex_count)
{
    _render_system->_setWorldMatrix(Ogre::Matrix4::IDENTITY);
    _render_system->_setProjectionMatrix(Ogre::Matrix4::IDENTITY);
    _render_system->_setViewMatrix(Ogre::Matrix4::IDENTITY);

    if (texture != nullptr)
    {
        OgreGlue::OgreTexture* ogre_texture = texture.cast<OgreGlue::OgreTexture>();

        Ogre::TexturePtr ogre_texture_ptr = ogre_texture->GetTexture();

        if (!ogre_texture_ptr.isNull())
        {
            _render_system->_setTexture(0, true, ogre_texture_ptr);
            _render_system->_setTextureUnitFiltering(0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_NONE);
        }
    }

    OgreGlue::OgreVertexBuffer* vertex_buffer = gbuffer.cast<OgreGlue::OgreVertexBuffer>();
    Ogre::RenderOperation* rop = vertex_buffer->GetRenderOperation();
    rop->vertexData->vertexCount = vertex_count;

    _render_system->_render(*rop);
    ++_draw_calls;
    _vertices_count += vertex_count;
}
//------------------------------------------------------------------------------------------------//
void OgreRenderer::BeginRender()
{
    _draw_calls = 0;
    _vertices_count = 0;

#if 0
    _render_system->_setWorldMatrix(Ogre::Matrix4::IDENTITY);
    _render_system->_setViewMatrix(Ogre::Matrix4::IDENTITY);
    _render_system->_setProjectionMatrix(Ogre::Matrix4::IDENTITY);
#else
    _render_system->_setWorldMatrix(_world_matrix);
#endif

    _render_system->setLightingEnabled(false);
    _render_system->_setDepthBufferParams(true, true);

    _render_system->_setCullingMode(Ogre::CULL_NONE);
    _render_system->_setFog(Ogre::FOG_NONE);
    _render_system->_setColourBufferWriteEnabled(true, true, true, true);
    _render_system->unbindGpuProgram(Ogre::GPT_FRAGMENT_PROGRAM);
    _render_system->unbindGpuProgram(Ogre::GPT_VERTEX_PROGRAM);
    _render_system->setShadingType(Ogre::SO_GOURAUD);

    _render_system->_setTextureCoordCalculation(0, Ogre::TEXCALC_NONE);
    _render_system->_setTextureCoordSet(0, 0);
#if 1
    _render_system->_setTextureUnitFiltering(0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_NONE);
#else
    _render_system->_setTextureUnitFiltering(0, Ogre::FO_NONE, Ogre::FO_NONE, Ogre::FO_NONE);
#endif
    _render_system->_setTextureAddressingMode(0, _texture_address_mode);
    _render_system->_setTextureMatrix(0, Ogre::Matrix4::IDENTITY);
    _render_system->_setAlphaRejectSettings(Ogre::CMPF_GREATER, 32, false);
    _render_system->_setTextureBlendMode(0, _color_blend_mode);
    _render_system->_setTextureBlendMode(0, _alpha_blend_mode);
    _render_system->_disableTextureUnitsFrom(1);

    _render_system->_setSceneBlending(Ogre::SBF_SOURCE_ALPHA, Ogre::SBF_ONE_MINUS_SOURCE_ALPHA);

    _render_system->_setPolygonMode(_wireframe ? Ogre::PM_WIREFRAME : Ogre::PM_SOLID);



    //_scene->Update(0.016F);
    //_scene->Draw(this);
}
//------------------------------------------------------------------------------------------------//
void OgreRenderer::EndRender()
{

}
//------------------------------------------------------------------------------------------------//
void OgreRenderer::SetScale(float32_t value)
{
    _scale = value;
    _world_matrix = Ogre::Matrix4::IDENTITY;
    _world_matrix.setScale(Ogre::Vector3(_scale, -_scale, _scale));
}
//------------------------------------------------------------------------------------------------//
}
//------------------------------------------------------------------------------------------------//
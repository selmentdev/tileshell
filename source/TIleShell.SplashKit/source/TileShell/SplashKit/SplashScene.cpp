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
#include <TileShell/SplashKit/SplashScene.h>
#include <TileShell/Drawing/GeometryBuilder.h>
#include <TileShell/Drawing/ResourceFactory.h>
#include <TileShell/Drawing/TextureManager.h>
#include <TileShell/Drawing/FontManager.h>
#include <TileShell/Drawing/StyleManager.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Serialization
{
struct SplashElementValueSerializer
{
    static bool Deserialize(SplashKit::SplashElement& out_result, Xml::XmlNode* node)
    {
        if (node == nullptr)
        {
            return false;
        }

        // Texture
        string_t texture;

        if (!StringValueSerializer::Deserialize(texture, node->first_attribute("Texture")))
        {
            return false;
        }

        // Time
        float32_t time;

        if (!FloatValueSerializer::Deserialize(time, node->first_attribute("Time")))
        {
            return false;
        }

        // Fade In Time
        float32_t fade_in;

        if (!FloatValueSerializer::Deserialize(fade_in, node->first_attribute("FadeIn")))
        {
            return false;
        }

        // Fade Out Time
        float32_t fade_out;

        if (!FloatValueSerializer::Deserialize(fade_out, node->first_attribute("FadeOut")))
        {
            return false;
        }

        int32_t index;

        if (!Int32ValueSerializer::Deserialize(index, node->first_attribute("Index")))
        {
            return false;
        }

        out_result._index = index;
        out_result._tween_opacity.Frames[0].Value = 0.0F;
        out_result._tween_opacity.Frames[1].Value = 1.0F;
        out_result._tween_opacity.Frames[2].Value = 1.0F;
        out_result._tween_opacity.Frames[3].Value = 0.0F;

        out_result._tween_opacity.Frames[0].KeyTime = 0.0F;
        out_result._tween_opacity.Frames[1].KeyTime = fade_in;
        out_result._tween_opacity.Frames[2].KeyTime = fade_in + time;
        out_result._tween_opacity.Frames[3].KeyTime = fade_in + time + fade_out;

        out_result._texture = Drawing::TextureManager::GetTexture(texture);

        return true;
    }
};
}
namespace SplashKit
{

//------------------------------------------------------------------------------------------------//
SplashScene::SplashScene()
{
    _geometry_buffer = Drawing::ResourceFactory::CreateGeometryBuffer();
}
//------------------------------------------------------------------------------------------------//
SplashScene::~SplashScene()
{
}
//------------------------------------------------------------------------------------------------//
bool SplashScene::Load(const string_t& path)
{
    Xml::XmlFile file(path.c_str());

    Xml::XmlDocument document;
    document.parse<0>(file.data());

    Xml::XmlNode* node = document.first_node("SplashScene");

    if (node == nullptr)
    {
        return false;
    }

    return Deserialize(node);
}
//------------------------------------------------------------------------------------------------//
bool SplashScene::Deserialize(Xml::XmlNode* node)
{
    if (node == nullptr)
    {
        return false;
    }

    Xml::XmlNode* item = node->first_node("SplashScene.Element");

    while (item != nullptr)
    {
        SplashElement e;

        if (Serialization::SplashElementValueSerializer::Deserialize(e, item))
        {
            _splash_element_collection.push_back(e);
        }

        item = item->next_sibling("SplashScene.Element");
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool SplashScene::Draw(Drawing::IRenderFrameCallback* callback)
{
    // If there is no items, stop splash scene
    if (_splash_element_collection.empty())
    {
        return false;
    }

    callback->DoRenderScreen(
        _geometry_buffer,
        _splash_element_collection[0]._texture,
        _geometry_buffer->GetVertexCount());

    return true;
}
//------------------------------------------------------------------------------------------------//
bool SplashScene::Update(float32_t delta_time)
{
    // If there is no items, stop splash scene
    if (_splash_element_collection.empty())
    {
        return false;
    }

    // If current tween ends, skip to next
    if (_splash_element_collection[0]._tween_opacity.IsEnd())
    {
        _splash_element_collection.erase(_splash_element_collection.begin());

        // Second check, because that tween might be last
        if (_splash_element_collection.empty())
        {

            return false;
        }
    }

    // Normal process
    auto size = _splash_element_collection[0]._texture->GetSize();

    Drawing::GeometryBuilder builder;
    builder.Begin();
    {
        float32_t inv = _screen_size.GetInverseAspectRatio() * size.GetAspectRatio();

        float32_t width = inv;
        float32_t height = 1.0F;

        float32_t opacity;
        _splash_element_collection[0]._tween_opacity.Evaluate(opacity);

        Drawing::Vertex v[4];
        v[0].Color = Drawing::Color(opacity, opacity, opacity, opacity).ToUInt32();
        v[1].Color = Drawing::Color(opacity, opacity, opacity, opacity).ToUInt32();
        v[2].Color = Drawing::Color(opacity, opacity, opacity, opacity).ToUInt32();
        v[3].Color = Drawing::Color(opacity, opacity, opacity, opacity).ToUInt32();

        v[0].TexCoord = float32x2_t(0.0F, 0.0F);
        v[1].TexCoord = float32x2_t(0.0F, 1.0F);
        v[2].TexCoord = float32x2_t(1.0F, 1.0F);
        v[3].TexCoord = float32x2_t(1.0F, 0.0F);

        v[0].Position = float32x3_t(-width,  height, 0.0F);
        v[1].Position = float32x3_t(-width, -height, 0.0F);
        v[2].Position = float32x3_t( width, -height, 0.0F);
        v[3].Position = float32x3_t( width,  height, 0.0F);

        builder.AddQuad(v[0], v[1], v[2], v[3]);
    }
    builder.End(_geometry_buffer);

    _splash_element_collection[0]._tween_opacity.Increment(std::min(delta_time, 0.050F));

    return true;
}
//------------------------------------------------------------------------------------------------//
bool SplashScene::SkipSequence()
{
    if (!_splash_element_collection.empty())
    {
        // Set tween time to 3rd frame keytime. This means that we'll see only 'fade out' part of tween
        _splash_element_collection[0]._tween_opacity.Time = std::max(
                    _splash_element_collection[0]._tween_opacity.Frames[2].KeyTime,
                    _splash_element_collection[0]._tween_opacity.Time);
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
bool SplashScene::SkipAll()
{
    _splash_element_collection.clear();

    return true;
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
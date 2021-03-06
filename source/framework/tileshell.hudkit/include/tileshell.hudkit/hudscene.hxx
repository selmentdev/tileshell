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
#ifndef _TileShell_HudKit_HudScene_H__
#define _TileShell_HudKit_HudScene_H__

#include <tileshell.ui/iscene.hxx>
#include <tileshell.drawing/geometrybuffer.hxx>
#include <tileshell.drawing/texture.hxx>
#include <tileshell.drawing/style.hxx>
#include <tileshell.animation/tween.hxx>
#include <tileshell.drawing/texture.hxx>
#include <tileshell.hudkit/hudelement.hxx>

namespace TileShell::HudKit
{

    class HudScene : public UI::IScene
    {
    private:
        Drawing::GeometryBufferRef      _geometry_buffer;
        Drawing::GeometryBufferRef      _text_buffer;
        Drawing::StyleRef               _style;
        HudElementCollection            _elements;

    public:
        HudScene();
        virtual ~HudScene();

    public:
        virtual bool Load(const string_t& path) override;
        bool Deserialize(Xml::XmlNode* node);

    public:
        virtual bool Draw(Drawing::IRenderFrameCallback* callback) override;
        virtual bool Update(float32_t delta_time) override;
    };
    typedef Core::Reference<HudScene> HudSceneRef;
}

#endif /* _TileShell_HudKit_HudScene_H__ */
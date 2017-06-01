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
#ifndef _OgreGlue_OgreTexture_H__
#define _OgreGlue_OgreTexture_H__

#include <TileShell/Core/Referenced.h>
#include <TileShell/Drawing/Texture.h>

#include <OgreTexture.h>
#include <OgreTextureManager.h>

namespace OgreGlue
{
class OgreTexture : public TileShell::Drawing::Texture
{
private:
    TileShell::string_t     _name;
    Ogre::TexturePtr        _texture;

public:
    OgreTexture(const TileShell::string_t& name, const TileShell::string_t& group);

    virtual ~OgreTexture();

public:
    const TileShell::string_t& GetName() const
    {
        return _name;
    }

    Ogre::TexturePtr GetTexture()
    {
        return _texture;
    }

    void SetTexture(Ogre::TexturePtr& texture)
    {
        _texture = texture;
    }

    TileShell::Drawing::Size GetSize() override
    {
        //TODO: implement constructor
        TileShell::Drawing::Size out_result;
        out_result.Width    = static_cast<float32_t>(_texture->getWidth());
        out_result.Height   = static_cast<float32_t>(_texture->getHeight());
        return out_result;
    }
};

}

#endif /* _OgreGlue_OgreTexture_H__ */
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
#include <tileshell.drawing/texturemanager.hxx>
#include <tileshell.drawing/resourcefactory.hxx>

namespace TileShell::Drawing
{

    TextureManager::TextureCollection TextureManager::_texture_collection;

    bool TextureManager::Initialize()
    {
        return true;
    }

    bool TextureManager::Shutdown()
    {
        _texture_collection.clear();

        return true;
    }

    TextureRef TextureManager::GetTexture(const string_t& name)
    {
        TextureCollection::const_iterator it = _texture_collection.find(name);

        if (it != _texture_collection.end())
        {
            return it->second;
        }

        TextureRef texture = ResourceFactory::CreateTexture(name);
        _texture_collection.insert(std::make_pair(name, texture));

        return texture;
    }

    void TextureManager::ReleaseTexture(TextureRef texture)
    {
        for (TextureCollection::const_iterator it = _texture_collection.begin();
            it != _texture_collection.end();
            ++it)
        {
            if (it->second == texture)
            {
                _texture_collection.erase(it);
                return;
            }
        }
    }

}

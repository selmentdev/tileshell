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
#include <tileshell.drawing/font.hxx>
#include <tileshell.drawing/fontmanager.hxx>

namespace TileShell::Drawing
{

    FontManager::FontCollection FontManager::_font_collection;

    FontRef FontManager::GetFont(const string_t& name)
    {
        FontCollection::const_iterator it = _font_collection.find(name);

        if (it != _font_collection.end())
        {
            return it->second;
        }

        FontRef font(new Font());

        if (font->Load(name))
        {
            _font_collection.insert(std::make_pair(name, font));
            return font;
        }

        return FontRef(nullptr);
    }

    bool FontManager::Initialize()
    {
        return true;
    }

    bool FontManager::Shutdown()
    {
        _font_collection.clear();
        return true;
    }

}
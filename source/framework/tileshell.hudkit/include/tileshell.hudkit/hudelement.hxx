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

#include <tileshell.ui/visual.hxx>

#define TILESHELL_DECLARE_HUDELEMENTFACTORYMETHOD(_Class, _Identifier) \
    public: \
    __forceinline static TileShell::Core::StrongName GetTypeName() \
    { \
        return TileShell::Core::StrongName(_Identifier); \
    } \
    \
    __forceinline static TileShell::HudKit::HudElement* CreateInstance() \
    { \
        return new _Class(); \
    }

namespace TileShell::HudKit
{
    class HudScene;

    class HudElement
        : public UI::Visual
    {
    protected:
        HudScene*   _scene;

    public:
        HudElement();
        virtual ~HudElement();

    public:
        HudScene* GetScene() const
        {
            return _scene;
        }

        void SetScene(HudScene* value)
        {
            _scene = value;
        }
    };

    typedef std::vector<HudElement*>    HudElementCollection;
}


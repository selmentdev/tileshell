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
#include <TileShell/Device.h>
#include <TileShell/Drawing/FontManager.h>
#include <TileShell/Drawing/TextureManager.h>
#include <TileShell/Drawing/StyleManager.h>
#include <TileShell/Drawing/ResourceFactory.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
//------------------------------------------------------------------------------------------------//
bool Device::Initialize(ExternalResourceFactory* resource_factory)
{
    Drawing::ResourceFactory::Initialize(resource_factory);
    Drawing::TextureManager::Initialize();
    Drawing::FontManager::Initialize();
    Drawing::StyleManager::Initialize();
    return true;
}
//------------------------------------------------------------------------------------------------//
bool Device::Shutdown()
{
    Drawing::StyleManager::Shutdown();
    Drawing::FontManager::Shutdown();
    Drawing::TextureManager::Shutdown();
    Drawing::ResourceFactory::Shutdown();
    return true;
}
//------------------------------------------------------------------------------------------------//
}
//------------------------------------------------------------------------------------------------//
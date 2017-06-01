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
#include "../Demo/GameManager.h"
#include "../Demo/IntroGameState.h"
#include "../Demo/PlayGameState.h"
#include "../Demo/MenuGameState.h"
#include "../OgreGlue/OgreRenderResourceFactory.h"

#include <TileShell/Device.h>
#include <TileShell/Core/Allocator.h>
#include <TileShell/UI/Controls/ControlFactory.h>
#include <TileShell/HudKit/HudElementFactory.h>

INT __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    {
        OgreGlue::OgreRenderResourceFactory factory;
        TileShell::Device::Initialize(&factory);

        Demo::GameManager game;
        game.Initialize();

        TileShell::UI::Controls::RegisterControls controls_registry;
        TileShell::HudKit::RegisterHudElements hudelement_registry;

        try
        {
            game.Start(Demo::IntroGameState::getInstance());
        }
        catch (Ogre::Exception& e)
        {
            MessageBoxA(nullptr, e.getFullDescription().c_str(), "Error", MB_OK | MB_ICONERROR | MB_TASKMODAL);
        }

        // Release resources (bad singleton design..)
        Demo::IntroGameState::getInstance()->ReleaseResources();
        Demo::PlayGameState::getInstance()->ReleaseResources();
        Demo::MenuGameState::getInstance()->ReleaseResources();

        TileShell::Device::Shutdown();

        game.Shutdown();
    }

#if 1
    Ogre::String memory = "Memory leaked: 0 bytes. Allocation peak: ";
    memory += Ogre::StringConverter::toString(TileShell::Core::MemoryStats::GetMemoryPeak());
    memory += " bytes.";

    MessageBoxA(nullptr, memory.c_str(), "Memory Status", MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
#endif

    return 0;
}


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
#include "IntroGameState.h"
#include "MenuGameState.h"

#include "../OgreSdk/DotSceneLoader.h"

#include <TileShell/SplashKit/SplashScene.h>

namespace Demo
{

IntroGameState IntroGameState::_game_state;

IntroGameState::IntroGameState()
    : _root(nullptr)
    , _scene_manager(nullptr)
    , _viewport(nullptr)
    , _camera(nullptr)
    , _exit_game(false)
#ifdef _DEBUG
    , _camera_manager(nullptr)
#endif
{
}

bool IntroGameState::OnLoad()
{
    _root               = Ogre::Root::getSingletonPtr();
    _scene_manager      = _root->createSceneManager(Ogre::ST_GENERIC);

#if 0
    DotSceneLoader loader;
    loader.parseDotScene("scene.scene", "MainMenu", _scene_manager);

    _camera             = _scene_manager->getCamera("Camera");
#else
    _camera = _scene_manager->createCamera("Camera");
    _camera->setPosition(Ogre::Vector3(00.0F, 00.0F, 2.0F));
    _camera->setFarClipDistance(1000.0F);
    _camera->setNearClipDistance(0.001F);
    _camera->lookAt(0.0F, 0.0F, 0.0F);
#endif
    _camera->setAspectRatio(1.78F);

    _scene_manager->addRenderQueueListener(&_renderer);

    _scene              = new TileShell::SplashKit::SplashScene();
    _scene->Load("../media/splash.xml");

    _renderer.SetScene(_scene.cast<TileShell::UI::IScene>());
    _renderer.SetScale(0.01F);

    _scene_manager->addRenderQueueListener(&_renderer);

    return GameState::OnLoad();
}

bool IntroGameState::OnUnload()
{
    _scene_manager->removeRenderQueueListener(&_renderer);
    delete _scene_manager;
    return GameState::OnUnload();
}

void IntroGameState::ActivateViewport()
{
    _root               = Ogre::Root::getSingletonPtr();
    _viewport           = _root->getAutoCreatedWindow()->addViewport(_camera);
    _viewport->setBackgroundColour(Ogre::ColourValue(0.0F, 0.0F, 0.0F));
}

void IntroGameState::DeactivateViewport()
{
    _root->getAutoCreatedWindow()->removeAllViewports();
}

void IntroGameState::Enter()
{
    GameState::Enter();

    _exit_game = false;
}

void IntroGameState::Exit()
{
    GameState::Exit();
}

void IntroGameState::Pause()
{
    GameState::Pause();
}

void IntroGameState::Resume()
{
    GameState::Resume();
}

bool IntroGameState::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    return true;
}

bool IntroGameState::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    return true;
}

bool IntroGameState::mouseMoved(const OIS::MouseEvent& evt)
{
    return true;
}

bool IntroGameState::keyPressed(const OIS::KeyEvent& evt)
{
    if (evt.key == OIS::KC_SPACE)
    {
        _scene.cast<TileShell::SplashKit::SplashScene>()->SkipSequence();
    }
    else if (evt.key == OIS::KC_ESCAPE)
    {
        _scene.cast<TileShell::SplashKit::SplashScene>()->SkipAll();
    }
    else if (evt.key == OIS::KC_F1)
    {
        _renderer.SetWireframe(!_renderer.GetWireframe());
    }
    else if (evt.key == OIS::KC_F12)
    {
        GameManager::getSingleton().SaveScreenShot();
    }

#if defined(_DEBUG)
    else if (evt.key == OIS::KC_F2)
    {
        ChangeState(MenuGameState::getInstance());
    }

#endif

    return true;
}

bool IntroGameState::keyReleased(const OIS::KeyEvent& evt)
{
    return true;
}

bool IntroGameState::frameStarted(const Ogre::FrameEvent& evt)
{
    TileShell::Drawing::Size screen_size;
    GameManager::getSingleton().GetWindowSize(
        screen_size.Width,
        screen_size.Height);

    _scene->SetScreenSize(screen_size);
    return true;
}

bool IntroGameState::frameEnded(const Ogre::FrameEvent& evt)
{
    if (!_scene->Update(evt.timeSinceLastFrame))
    {
        ChangeState(MenuGameState::getInstance());
    }

    if (_exit_game)
    {
        return false;
    }

    return true;
}

bool IntroGameState::ReleaseResources()
{
    _scene  = nullptr;
    return GameState::ReleaseResources();
}

}


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
#include "PlayGameState.h"
#include "IntroGameState.h"
#include "MenuGameState.h"

namespace Demo
{

PlayGameState PlayGameState::_game_state;

PlayGameState::PlayGameState()
    : _root(nullptr)
    , _scene_manager(nullptr)
    , _viewport(nullptr)
    , _camera(nullptr)
    , _exit_game(false)
{
}

void PlayGameState::ActivateViewport()
{
    _root               = Ogre::Root::getSingletonPtr();
    _viewport           = _root->getAutoCreatedWindow()->addViewport(_camera);
    _viewport->setBackgroundColour(Ogre::ColourValue(0.0F, 1.0F, 0.0F));
}

void PlayGameState::DeactivateViewport()
{
    _root->getAutoCreatedWindow()->removeAllViewports();
}

bool PlayGameState::OnLoad()
{
    _root               = Ogre::Root::getSingletonPtr();
    _scene_manager      = _root->createSceneManager(Ogre::ST_GENERIC);
    _camera             = _scene_manager->createCamera("DefaultCamera");
    _camera->setAspectRatio(1.78F);
    _scene_manager->addRenderQueueListener(&_renderer);

    return GameState::OnLoad();
}

bool PlayGameState::OnUnload()
{
    _scene_manager->removeRenderQueueListener(&_renderer);
    delete _scene_manager;
    return GameState::OnUnload();
}

void PlayGameState::Enter()
{
    GameState::Enter();
}

void PlayGameState::Exit()
{
    GameState::Exit();
}

void PlayGameState::Pause()
{
    GameState::Pause();
}

void PlayGameState::Resume()
{
    GameState::Resume();
}

bool PlayGameState::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    return true;
}

bool PlayGameState::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    return true;
}

bool PlayGameState::mouseMoved(const OIS::MouseEvent& evt)
{
    return true;
}

bool PlayGameState::keyPressed(const OIS::KeyEvent& evt)
{
    if (evt.key == OIS::KC_P)
    {
        PopState(); //(PauseGameState::getInstance());
    }

    return true;
}

bool PlayGameState::keyReleased(const OIS::KeyEvent& evt)
{
    return true;
}

bool PlayGameState::frameStarted(const Ogre::FrameEvent& evt)
{
    return true;
}

bool PlayGameState::frameEnded(const Ogre::FrameEvent& evt)
{
    if (_exit_game)
    {
        return false;
    }

    return true;
}

bool PlayGameState::ReleaseResources()
{
    //_scene  = nullptr;
    return GameState::ReleaseResources();
}

}


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
#ifndef _Demo_IntroGameState_H__
#define _Demo_IntroGameState_H__
//------------------------------------------------------------------------------------------------//
#include "GameState.h"
#include <SdkCameraMan.h>
//------------------------------------------------------------------------------------------------//
namespace Demo
{
class IntroGameState
    : public GameState
{
public:
    virtual bool OnLoad() override;
    virtual bool OnUnload() override;

    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Pause() override;
    virtual void Resume() override;

    virtual void ActivateViewport() override;
    virtual void DeactivateViewport() override;

    virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id) override;
    virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id) override;
    virtual bool mouseMoved(const OIS::MouseEvent& evt) override;
    virtual bool keyPressed(const OIS::KeyEvent& evt) override;
    virtual bool keyReleased(const OIS::KeyEvent& evt) override;

    virtual bool frameStarted(const Ogre::FrameEvent& evt) override;
    virtual bool frameEnded(const Ogre::FrameEvent& evt) override;

    static IntroGameState* getInstance()
    {
        return &_game_state;
    }

    virtual bool ReleaseResources() override;
protected:
    IntroGameState();

protected:
    Ogre::Root*             _root;
    Ogre::SceneManager*     _scene_manager;
    Ogre::Viewport*         _viewport;
    Ogre::Camera*           _camera;
    bool                    _exit_game;

#ifdef _DEBUG
    OgreBites::SdkCameraMan _camera_manager;
#endif

protected:
    TileShell::UI::ISceneRef        _scene;

private:
    static IntroGameState   _game_state;
};
//------------------------------------------------------------------------------------------------//
}
//------------------------------------------------------------------------------------------------//
#endif /* _Demo_IntroGameState_H__ */
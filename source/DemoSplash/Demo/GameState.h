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
#ifndef _Demo_GameState_H__
#define _Demo_GameState_H__

#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreRenderSystem.h>
#include <OgreViewport.h>
#include <OgreWindowEventUtilities.h>
#include <OgreRenderQueueListener.h>
#include <OIS/OIS.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include "../OgreGlue/OgreRenderer.h"
#include "GameManager.h"

namespace Demo
{

class GameState
{
protected:
    OgreGlue::OgreRenderer      _renderer;

public:
    void Load()
    {
        if (_loaded == false)
        {
            OnLoad();
            _loaded = true;
        }
    }

    void Unload()
    {
    }

public:
    virtual bool OnLoad();
    virtual bool OnUnload();

    virtual void Enter();
    virtual void Exit();
    virtual void Pause();
    virtual void Resume();

    virtual void ActivateViewport() = 0;
    virtual void DeactivateViewport() = 0;

    virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id) = 0;
    virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id) = 0;
    virtual bool mouseMoved(const OIS::MouseEvent& evt) = 0;
    virtual bool keyPressed(const OIS::KeyEvent& evt) = 0;
    virtual bool keyReleased(const OIS::KeyEvent& evt) = 0;

    virtual bool frameStarted(const Ogre::FrameEvent& evt) = 0;
    virtual bool frameEnded(const Ogre::FrameEvent& evt) = 0;

    virtual bool ReleaseResources();

public:
    void ChangeState(GameState* state)
    {
        GameManager::getSingletonPtr()->ChangeState(state);
    }

    void PushState(GameState* state)
    {
        GameManager::getSingletonPtr()->PushState(state);
    }

    void PopState()
    {
        GameManager::getSingletonPtr()->PopState();
    }

protected:
    GameState();

private:
    bool        _loaded;
};

}

#endif /* _Demo_GameState_H__ */
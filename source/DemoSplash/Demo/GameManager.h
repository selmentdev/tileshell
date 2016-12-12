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
#ifndef _Demo_GameManager_H__
#define _Demo_GameManager_H__
//------------------------------------------------------------------------------------------------//
#include <Ogre/Ogre.h>
#include <Ogre/OgreFrameListener.h>
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreConfigFile.h>
#include <OIS/OIS.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>
#include <TileShell/Required.h>
//------------------------------------------------------------------------------------------------//
namespace Demo
{
class GameState;

class GameManager
    : public Ogre::FrameListener
    , public OIS::KeyListener
    , public OIS::MouseListener
    , public Ogre::Singleton<GameManager>
{
public:
    GameManager();
    virtual ~GameManager();

    bool Initialize();
    bool Shutdown();

    void Start(GameState* state);
    void ChangeState(GameState* state);
    void PushState(GameState* state);
    void PopState();

    static GameManager& getSingleton();
    static GameManager* getSingletonPtr();

    virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id) override;
    virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id) override;
    virtual bool mouseMoved(const OIS::MouseEvent& evt) override;
    virtual bool keyPressed(const OIS::KeyEvent& evt) override;
    virtual bool keyReleased(const OIS::KeyEvent& evt) override;

    virtual bool frameStarted(const Ogre::FrameEvent& evt) override;
    virtual bool frameEnded(const Ogre::FrameEvent& evt) override;

    bool Run();

    float GetAverageFPS() const
    {
        return _render_window->getAverageFPS();
    }

    float GetBestFPS() const
    {
        return _render_window->getBestFPS();
    }

    float GetWorstFPS() const
    {
        return _render_window->getWorstFPS();
    }

    float GetWorstFrameTime() const
    {
        return _render_window->getWorstFrameTime();
    }

    float GetBestFrameTime() const
    {
        return _render_window->getBestFrameTime();
    }

    float GetLastFrameTime() const
    {
        return 1.0F / _render_window->getStatistics().lastFPS;
    }

    void GetWindowSize(float& out_width, float& out_height)
    {
        out_width = static_cast<float>(_render_window->getWidth());
        out_height = static_cast<float>(_render_window->getHeight());
    }

    TileShell::string_t SaveScreenShot()
    {
        return _render_window->writeContentsToTimestampedFile("tileshell-", ".png").c_str();
    }
protected:
    Ogre::Root*             _root;
    Ogre::RenderWindow*     _render_window;
    OIS::InputManager*      _input_manager;
    OIS::Mouse*             _mouse;
    OIS::Keyboard*          _keyboard;

protected:
    void SetupResources();
    bool Configure();

private:
    std::vector<GameState*>     _states;
};
//------------------------------------------------------------------------------------------------//
}
//------------------------------------------------------------------------------------------------//
#endif /* _Demo_GameManager_H__ */
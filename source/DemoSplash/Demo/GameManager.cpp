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
#include "GameManager.h"
#include "GameState.h"

#include "../OgreGlue/OgreRenderResourceFactory.h"

template<> Demo::GameManager* Ogre::Singleton<Demo::GameManager>::msSingleton = nullptr;

namespace Demo
{

    GameManager::GameManager()
        : _root(nullptr)
        , _render_window(nullptr)
        , _input_manager(nullptr)
        , _mouse(nullptr)
        , _keyboard(nullptr)
    {
    }

    GameManager::~GameManager()
    {
        while (!_states.empty())
        {
            _states.back()->Exit();
            _states.pop_back();
        }

        assert(_input_manager != nullptr);

        _input_manager->destroyInputObject(_mouse);
        _input_manager->destroyInputObject(_keyboard);
        OIS::InputManager::destroyInputSystem(_input_manager);

        if (_root)
        {
            delete _root;
        }
    }

    bool GameManager::Initialize()
    {
        return true;
    }

    bool GameManager::Shutdown()
    {
        return true;
    }

    void GameManager::Start(GameState* state)
    {
        _root = new Ogre::Root();

        if (!Configure())
        {
            return;
        }

        SetupResources();

        _root->addFrameListener(this);

        // Get window handle needed for input handling.
        size_t hwnd = 0;
        _render_window->getCustomAttribute("WINDOW", &hwnd);

        // Create input manager
        _input_manager = OIS::InputManager::createInputSystem(hwnd);

        _mouse = static_cast<OIS::Mouse*>(_input_manager->createInputObject(OIS::OISMouse, true));
        _keyboard = static_cast<OIS::Keyboard*>(_input_manager->createInputObject(OIS::OISKeyboard, true));

        _mouse->setEventCallback(this);
        _keyboard->setEventCallback(this);

        uint32_t width, height, depth;
        int32_t left, top;

        _render_window->getMetrics(width, height, depth, left, top);

        const OIS::MouseState& mouse_state = _mouse->getMouseState();
        mouse_state.width = width;
        mouse_state.height = height;

        ChangeState(state);

        Run();
    }

    void GameManager::ChangeState(GameState* state)
    {
        if (!_states.empty())
        {
            _states.back()->Exit();
            _states.pop_back();
        }

        _states.push_back(state);
        _states.back()->Enter();
    }

    void GameManager::PushState(GameState* state)
    {
        if (!_states.empty())
        {
            _states.back()->Pause();
        }

        _states.push_back(state);
        _states.back()->Enter();
    }

    void GameManager::PopState()
    {
        if (!_states.empty())
        {
            _states.back()->Exit();
            _states.pop_back();
        }

        if (!_states.empty())
        {
            _states.back()->Resume();
        }
    }

    void GameManager::SetupResources()
    {
        Ogre::ConfigFile cf;
        cf.load("resources_d.cfg");

        Ogre::ConfigFile::SectionIterator si = cf.getSectionIterator();

        Ogre::String section_name, type_name, archive_name;

        Ogre::ResourceGroupManager& resource_group_manager = Ogre::ResourceGroupManager::getSingleton();

        while (si.hasMoreElements())
        {
            section_name = si.peekNextKey();

            Ogre::ConfigFile::SettingsMultiMap* settings = si.getNext();
            Ogre::ConfigFile::SettingsMultiMap::iterator it;

            for (it = settings->begin(); it != settings->end(); ++it)
            {
                type_name = it->first;
                archive_name = it->second;

                resource_group_manager.addResourceLocation(archive_name, type_name, section_name);
            }
        }

        resource_group_manager.initialiseAllResourceGroups();
    }

    bool GameManager::Configure()
    {
        if (!_root->restoreConfig())
        {
            if (!_root->showConfigDialog())
            {
                return false;
            }
        }

        _render_window = _root->initialise(true, "TileShell Library Demo");

        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

        return true;
    }

    bool GameManager::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
    {
        return _states.back()->mousePressed(evt, id);
    }

    bool GameManager::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
    {
        return _states.back()->mouseReleased(evt, id);
    }

    bool GameManager::mouseMoved(const OIS::MouseEvent& evt)
    {
        return _states.back()->mouseMoved(evt);
    }

    bool GameManager::keyPressed(const OIS::KeyEvent& evt)
    {
        return _states.back()->keyPressed(evt);
    }

    bool GameManager::keyReleased(const OIS::KeyEvent& evt)
    {
        return _states.back()->keyReleased(evt);
    }

    bool GameManager::frameStarted(const Ogre::FrameEvent& evt)
    {
        return _states.back()->frameStarted(evt);
    }

    bool GameManager::frameEnded(const Ogre::FrameEvent& evt)
    {
        return _states.back()->frameEnded(evt);
    }

    GameManager* GameManager::getSingletonPtr()
    {
        return msSingleton;
    }

    GameManager& GameManager::getSingleton()
    {
        assert(msSingleton);
        return *msSingleton;
    }

    bool GameManager::Run()
    {
        for (;;)
        {
            Ogre::WindowEventUtilities::messagePump();

            if (_render_window->isClosed())
            {
                return true;
            }

            if (_mouse != nullptr)
            {
                _mouse->capture();
            }

            if (_keyboard != nullptr)
            {
                _keyboard->capture();
            }

            if (_root->renderOneFrame() == false)
            {
                return false;
            }
        }

        return true;
    }
}

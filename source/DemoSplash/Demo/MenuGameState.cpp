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
#include "MenuGameState.h"
#include "IntroGameState.h"
#include "PlayGameState.h"
//------------------------------------------------------------------------------------------------//
#include "../OgreSdk/DotSceneLoader.h"
//------------------------------------------------------------------------------------------------//
#include <TileShell/Serialization/TypeSerializer.h>
#include <TileShell/UI/Controls/MenuScene.h>
#include <TileShell/UI/Controls/Activity.h>
#include <TileShell/UI/Controls/MenuScene.h>
#include <TileShell/UI/Controls/Primitives/ButtonBase.h>
#include <TileShell/UI/Controls/Primitives/RangeBase.h>
#include <TileShell/UI/Controls/Primitives/SelectorBase.h>
#include <TileShell/UI/Controls/Primitives/TextBase.h>
#include <TileShell/UI/Controls/Primitives/ToggleButton.h>
//------------------------------------------------------------------------------------------------//
using namespace TileShell::Core;
using namespace TileShell::UI::Controls;
//------------------------------------------------------------------------------------------------//
namespace Demo
{
//------------------------------------------------------------------------------------------------//
class MainMenuHandler : public TileShell::UI::Controls::IEventHandler
{
private:
    TileShell::UI::Controls::Activity* _activity;

public:
    virtual ~MainMenuHandler() { }

public:
    TileShell::UI::Controls::Activity* GetActivity() const
    {
        return _activity;
    }

public:
    virtual bool Load(TileShell::UI::Controls::Activity* activity)
    {
        if (activity == nullptr)
        {
            return false;
        }

        // Store activity for future
        _activity = activity;

        // Set event handler
        _activity->SetEventHandler(this);

        return activity != nullptr;
    }
};
//------------------------------------------------------------------------------------------------//
class Menu_Main_ExitGame : public MainMenuHandler
{
public:
    virtual ~Menu_Main_ExitGame() { }

public:
    virtual void OnCommand(Primitives::ButtonBase* control) override
    {
        // Exit from game command
        if (control->GetTargetActivity() == StrongName("Menu.Main.Exit.Exit"))
        {
            MenuGameState::getInstance()->ExitGame();
        }
    }
};
//------------------------------------------------------------------------------------------------//
class Menu_Main_Menu : public MainMenuHandler
{
private:
    Primitives::TextBase*   debug_OutputDbg;
    Primitives::TextBase*   tbx_Spinner1;
    Primitives::TextBase*   tbx_Spinner2;
    Primitives::TextBase*   tbx_Spinner3;
    Primitives::TextBase*   tbx_Spinner4;
    float32_t               _counter;

public:
    virtual ~Menu_Main_Menu() { }

public:
    virtual bool Load(Activity* activity) override
    {
        _counter = 0.0F;

        if (!MainMenuHandler::Load(activity))
        {
            return false;
        }

        debug_OutputDbg = dynamic_cast<Primitives::TextBase*>(GetActivity()->GetControlByName(
                              StrongName("debug_OutputDbg")));
        tbx_Spinner1    = dynamic_cast<Primitives::TextBase*>(GetActivity()->GetControlByName(
                              StrongName("Spinner1")));
        tbx_Spinner2    = dynamic_cast<Primitives::TextBase*>(GetActivity()->GetControlByName(
                              StrongName("Spinner2")));
        tbx_Spinner3    = dynamic_cast<Primitives::TextBase*>(GetActivity()->GetControlByName(
                              StrongName("Spinner3")));
        tbx_Spinner4    = dynamic_cast<Primitives::TextBase*>(GetActivity()->GetControlByName(
                              StrongName("Spinner4")));

        return true;
    }

    virtual void OnUpdate(Activity* activity, float32_t delta_time) override
    {
        _counter += delta_time;

        char buffer[256];
        /*_snprintf_s(buffer, 255, "A:%3.2f,B:%3.2f,W:%3.2f,BT:%3.2f,WT:%3.2f",
            GameManager::getSingleton().GetAverageFPS(),
            GameManager::getSingleton().GetBestFPS(),
            GameManager::getSingleton().GetWorstFPS(),
            GameManager::getSingleton().GetBestFrameTime(),
            GameManager::getSingleton().GetWorstFrameTime());*/

        auto tsft = MenuGameState::getInstance()->GetTileshellFrameTime();
        double fps = static_cast<double>(GameManager::getSingleton().GetAverageFPS());
        auto ft = 1.0 / fps;
        auto pc = (tsft / ft) * 100.0;

        _snprintf_s(buffer, 255, "[TS-FT: %03.4f, (FT: %03.4f, FPS: %03.2f)], PC: %03.2f",
                    tsft, ft, fps, pc);


        debug_OutputDbg->SetText(buffer);

        float32_t update1 = 35.0F * delta_time;
        float32_t update2 = std::sin(_counter) * 1.5F;
        float32_t update3 = std::cos(_counter) * 3.0F + update2 * 0.5F;
        float32_t update4 = -25.0F * delta_time;

        tbx_Spinner1->SetRotateTransform(TileShell::Drawing::RotateTransform(
                                             tbx_Spinner1->GetRotateTransform().Angle + update1));
        tbx_Spinner2->SetRotateTransform(TileShell::Drawing::RotateTransform(
                                             tbx_Spinner2->GetRotateTransform().Angle + update2));
        tbx_Spinner3->SetRotateTransform(TileShell::Drawing::RotateTransform(
                                             tbx_Spinner3->GetRotateTransform().Angle + update3));
        tbx_Spinner4->SetRotateTransform(TileShell::Drawing::RotateTransform(
                                             tbx_Spinner4->GetRotateTransform().Angle + update4));
        tbx_Spinner1->SetZOrder(10.0F + std::sin(_counter * 0.5F) * 30.0F);
        tbx_Spinner2->SetZOrder(15.0F + std::sin(_counter * 0.25F) * 40.0F);
        tbx_Spinner3->SetZOrder(10.0F + std::sin(_counter * 0.35F) * 30.0F);
        tbx_Spinner4->SetZOrder(20.0F + std::sin(_counter * 0.65F) * 40.0F);
    }
};
//------------------------------------------------------------------------------------------------//
class Menu_Main_Options_Video : public MainMenuHandler
{
private:
    Primitives::RangeBase* sdr_Stereo3DCovergence;

public:
    virtual ~Menu_Main_Options_Video() { }


    virtual bool Load(Activity* activity) override
    {
        if (!MainMenuHandler::Load(activity))
        {
            return false;
        }

        sdr_Stereo3DCovergence = dynamic_cast<Primitives::RangeBase*>(GetActivity()->GetControlByName(
                                     StrongName("sdr_Stereo3DCovergence")));

        return true;
    }

    virtual void OnValueChanged(Primitives::RangeBase* control) override
    {
        if (control->GetName() == StrongName("sdr_Brightness"))
        {
            sdr_Stereo3DCovergence->SetRangeMin(control->GetRangeMin());
            sdr_Stereo3DCovergence->SetRangeMax(control->GetRangeMax());
            sdr_Stereo3DCovergence->SetValue(control->GetValue());
        }
    }
};
//------------------------------------------------------------------------------------------------//
class Menu_Main_Options_Audio : public MainMenuHandler
{
private:
    Primitives::TextBase*   debug_OutputDbg;
    Primitives::RangeBase*  debug_Progress;
public:
    virtual ~Menu_Main_Options_Audio() { }

public:
    virtual bool Load(Activity* activity) override
    {
        if (!MainMenuHandler::Load(activity))
        {
            return false;
        }

        debug_OutputDbg = dynamic_cast<Primitives::TextBase*>(GetActivity()->GetControlByName(
                              StrongName("debug_OutputDbg")));
        debug_Progress = dynamic_cast<Primitives::RangeBase*>(GetActivity()->GetControlByName(
                             StrongName("debug_Progress")));

        return true;
    }

    virtual void OnSelectionChanged(Primitives::SelectorBase* control) override
    {
        Primitives::SelectorItem item;
        control->GetSelectedItem(item);
        debug_OutputDbg->SetText(item._text);

        debug_Progress->SetRangeMin(0.0F);
        debug_Progress->SetRangeMax(static_cast<float32_t>(control->GetItemsCount()));
        debug_Progress->SetValue(static_cast<float32_t>(control->GetSelectedItemIndex() + 1));
    }

    virtual void OnValueChanged(Primitives::RangeBase* control) override
    {
        if (control->GetName() != StrongName("debug_Progress"))
        {
            debug_Progress->SetRangeMin(control->GetRangeMin());
            debug_Progress->SetRangeMax(control->GetRangeMax());
            debug_Progress->SetValue(control->GetValue());

            char buffer[64];
            _snprintf_s(buffer, 63, "Progress: %1.0f", control->GetPercentage() * 100.0F);
            debug_OutputDbg->SetText(buffer);
        }
    }
};
//------------------------------------------------------------------------------------------------//
class Menu_Main_Options_KeyBindings : public MainMenuHandler
{
public:
    virtual ~Menu_Main_Options_KeyBindings() { }
};
//------------------------------------------------------------------------------------------------//
class Menu_Main_Options_Gameplay : public MainMenuHandler
{
public:
    virtual ~Menu_Main_Options_Gameplay() { }
};
//------------------------------------------------------------------------------------------------//
class Menu_Main_Options_Controls : public MainMenuHandler
{
private:
    Primitives::RangeBase*      sdr_RotationAngle;
    Primitives::RangeBase*      sdr_ScaleX;
    Primitives::RangeBase*      sdr_ScaleY;
    Primitives::RangeBase*      sdr_SkewX;
    Primitives::RangeBase*      sdr_SkewY;
    Primitives::RangeBase*      sdr_TranslateX;
    Primitives::RangeBase*      sdr_TranslateY;
    Primitives::RangeBase*      sdr_ZOrder;
    Primitives::ButtonBase*     btn_Object;
    Primitives::ToggleButton*   chb_Automate;
    float32_t                   counter;
    bool                        automate;

public:
    Menu_Main_Options_Controls()
        : sdr_RotationAngle(nullptr)
        , sdr_ScaleX(nullptr)
        , sdr_ScaleY(nullptr)
        , sdr_SkewX(nullptr)
        , sdr_SkewY(nullptr)
        , sdr_TranslateX(nullptr)
        , sdr_TranslateY(nullptr)
        , sdr_ZOrder(nullptr)
        , chb_Automate(nullptr)
        , counter(0.0F)
        , automate(false)
    {
    }

    virtual ~Menu_Main_Options_Controls() { }

public:
    virtual bool Load(Activity* activity) override
    {
        if (!MainMenuHandler::Load(activity))
        {
            return false;
        }

        sdr_RotationAngle   = dynamic_cast<Primitives::RangeBase*>(GetActivity()->GetControlByName(
                                  StrongName("sdr_RotationAngle")));
        sdr_ScaleX          = dynamic_cast<Primitives::RangeBase*>(GetActivity()->GetControlByName(
                                  StrongName("sdr_ScaleX")));
        sdr_ScaleY          = dynamic_cast<Primitives::RangeBase*>(GetActivity()->GetControlByName(
                                  StrongName("sdr_ScaleY")));
        sdr_SkewX           = dynamic_cast<Primitives::RangeBase*>(GetActivity()->GetControlByName(
                                  StrongName("sdr_SkewX")));
        sdr_SkewY           = dynamic_cast<Primitives::RangeBase*>(GetActivity()->GetControlByName(
                                  StrongName("sdr_SkewY")));
        sdr_TranslateX      = dynamic_cast<Primitives::RangeBase*>(GetActivity()->GetControlByName(
                                  StrongName("sdr_TranslateX")));
        sdr_TranslateY      = dynamic_cast<Primitives::RangeBase*>(GetActivity()->GetControlByName(
                                  StrongName("sdr_TranslateY")));
        sdr_ZOrder          = dynamic_cast<Primitives::RangeBase*>(GetActivity()->GetControlByName(
                                  StrongName("sdr_ZOrder")));
        btn_Object          = dynamic_cast<Primitives::ButtonBase*>(GetActivity()->GetControlByName(
                                  StrongName("btn_Object")));
        chb_Automate        = dynamic_cast<Primitives::ToggleButton*>(GetActivity()->GetControlByName(
                                  StrongName("chb_Automate")));

        return true;
    }

    virtual void OnUpdate(Activity* activity, float32_t delta_time) override
    {
        using namespace TileShell::Drawing;

        tileshell_unused(activity);

        if (automate)
        {
            counter += delta_time;

            ScaleTransform xscale(
                std::min(std::max(0.5F, std::sin(counter * 0.225F) * 2.0F), 2.0F),
                std::min(std::max(0.5F, std::cos(counter * 0.250F) * 2.0F), 2.0F)
            );
            TranslateTransform xtranslate(
                std::sin(counter * 0.443F) * 300.0F,
                std::cos(counter * 0.459F) * 300.0F
            );

            RotateTransform xrotate(
                std::sin(counter + std::cos(counter * 0.2F)) * 360.0F
            );

            float32_t zorder = std::sin(counter * 0.225F) * 25.0F + 35.0F;

            btn_Object->SetScaleTransform(xscale);
            btn_Object->SetTranslateTransform(xtranslate);
            btn_Object->SetRotateTransform(xrotate);

            sdr_ScaleX->SetValue(xscale.ScaleX);
            sdr_ScaleY->SetValue(xscale.ScaleY);
            sdr_TranslateX->SetValue(xtranslate.X);
            sdr_TranslateY->SetValue(xtranslate.Y);
            sdr_RotationAngle->SetValue(xrotate.Angle);
            sdr_ZOrder->SetValue(zorder);
        }
    }

    virtual void OnStateChanged(Primitives::ToggleButton* control) override
    {
        if (control == chb_Automate)
        {
            automate = chb_Automate->IsChecked();
        }
    }

    virtual void OnValueChanged(Primitives::RangeBase* control) override
    {
        using namespace TileShell::Drawing;

        if (!automate)
        {
            if (control == sdr_RotationAngle)
            {
                btn_Object->SetRotateTransform(RotateTransform(control->GetValue()));
            }
            else if (control == sdr_ScaleX)
            {
                btn_Object->SetScaleTransform(ScaleTransform(control->GetValue(),
                                              btn_Object->GetScaleTransform().ScaleY));
            }
            else if (control == sdr_ScaleY)
            {
                btn_Object->SetScaleTransform(ScaleTransform(btn_Object->GetScaleTransform().ScaleX,
                                              control->GetValue()));
            }
            else if (control == sdr_SkewX)
            {
                btn_Object->SetSkewTransform(SkewTransform(control->GetValue(),
                                             btn_Object->GetSkewTransform().AngleY));
            }
            else if (control == sdr_SkewY)
            {
                btn_Object->SetSkewTransform(SkewTransform(btn_Object->GetSkewTransform().AngleX,
                                             control->GetValue()));
            }
            else if (control == sdr_TranslateX)
            {
                btn_Object->SetTranslateTransform(TranslateTransform(control->GetValue(),
                                                  btn_Object->GetTranslateTransform().Y));
            }
            else if (control == sdr_TranslateY)
            {
                btn_Object->SetTranslateTransform(TranslateTransform(btn_Object->GetTranslateTransform().X,
                                                  control->GetValue()));
            }
            else if (control == sdr_ZOrder)
            {
                btn_Object->SetZOrder(sdr_ZOrder->GetValue());
            }
        }
    }
};
//------------------------------------------------------------------------------------------------//
MenuGameState MenuGameState::_game_state;
//------------------------------------------------------------------------------------------------//
MenuGameState::MenuGameState()
    : _mm_menu(nullptr)
    , _mm_menu_exit(nullptr)
    , _mm_options_video(nullptr)
    , _mm_options_audio(nullptr)
    , _mm_options_keybindings(nullptr)
    , _mm_options_gameplay(nullptr)
    , _mm_options_controls(nullptr)
    , _root(nullptr)
    , _scene_manager(nullptr)
    , _viewport(nullptr)
    , _camera(nullptr)
    , _exit_game(false)
    , _camera_manager(nullptr)
    , _camera_locked(true)
{
}
//------------------------------------------------------------------------------------------------//
void MenuGameState::ActivateViewport()
{
    _root               = Ogre::Root::getSingletonPtr();
    _viewport           = _root->getAutoCreatedWindow()->addViewport(_camera);
    _viewport->setBackgroundColour(Ogre::ColourValue(0.0F, 0.0F, 1.0F));
}
//------------------------------------------------------------------------------------------------//
void MenuGameState::DeactivateViewport()
{
    _root->getAutoCreatedWindow()->removeAllViewports();
}
//------------------------------------------------------------------------------------------------//
bool MenuGameState::OnLoad()
{
    _root               = Ogre::Root::getSingletonPtr();
    _scene_manager      = _root->createSceneManager(Ogre::ST_GENERIC);

    DotSceneLoader loader;
    loader.parseDotScene("scene.scene", "MainMenu", _scene_manager);

    _camera             = _scene_manager->getCamera("Camera");
    _camera->setAspectRatio(1.78F);

    _scene_manager->addRenderQueueListener(&_renderer);

    //
    // Load scene from xml
    //
    _scene = new TileShell::UI::MenuScene();
    _scene->Load("../media/mainmenu.xml");

    using namespace TileShell::Core;
    using namespace TileShell::UI;

    TileShell::UI::MenuScene* menu_scene = _scene.cast<TileShell::UI::MenuScene>();

    _mm_menu = new Menu_Main_Menu();
    _mm_menu_exit = new Menu_Main_ExitGame();
    _mm_options_video = new Menu_Main_Options_Video();
    _mm_options_audio = new Menu_Main_Options_Audio();
    _mm_options_keybindings = new Menu_Main_Options_KeyBindings();
    _mm_options_gameplay = new Menu_Main_Options_Gameplay();
    _mm_options_controls = new Menu_Main_Options_Controls();

    _mm_menu->Load(menu_scene->GetActivityByName(StrongName("Menu.Main")));
    _mm_menu_exit->Load(menu_scene->GetActivityByName(StrongName("Menu.Main.Exit")));
    _mm_options_video->Load(menu_scene->GetActivityByName(StrongName("Menu.Main.Options.Video")));
    _mm_options_audio->Load(menu_scene->GetActivityByName(StrongName("Menu.Main.Options.Audio")));
    _mm_options_keybindings->Load(menu_scene->GetActivityByName(
                                      StrongName("Menu.Main.Options.KeyBindings")));
    _mm_options_gameplay->Load(menu_scene->GetActivityByName(StrongName("Menu.Main.Options.Gameplay")));
    _mm_options_controls->Load(menu_scene->GetActivityByName(StrongName("Menu.Main.Options.Controls")));

    //
    // Set renderer scene
    //
    _renderer.SetScene(_scene.cast<TileShell::UI::IScene>());
    _renderer.SetScale(0.01F);

    //#ifdef _DEBUG
    _camera_manager.setCamera(_camera);
    _camera_manager.setStyle(OgreBites::CS_FREELOOK);
    _camera_manager.setTopSpeed(0.5F);
    //#endif

    uint64_t start, stop;

    {
        start = __rdtsc();
        {
            ::Sleep(1000);
        }
        stop = __rdtsc();
    }

    _ts_persecond = stop - start;



    return GameState::OnLoad();
}
//------------------------------------------------------------------------------------------------//
bool MenuGameState::OnUnload()
{
    return GameState::OnUnload();
}
//------------------------------------------------------------------------------------------------//
void MenuGameState::Enter()
{
    GameState::Enter();
}
//------------------------------------------------------------------------------------------------//
void MenuGameState::Exit()
{
    GameState::Exit();
}
//------------------------------------------------------------------------------------------------//
void MenuGameState::Pause()
{
    GameState::Pause();
}
//------------------------------------------------------------------------------------------------//
void MenuGameState::Resume()
{
    GameState::Resume();
}
//------------------------------------------------------------------------------------------------//
bool MenuGameState::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{

    if (_camera_locked == false)
    {
        _camera_manager.injectMouseDown(evt, id);
        return true;
    }


    TileShell::Input::MouseEventArgs e;
    e._absolute_x = static_cast<float32_t>(evt.state.X.abs);
    e._absolute_y = static_cast<float32_t>(evt.state.Y.abs);
    e._buttons = evt.state.buttons;
    e._relative_x = static_cast<float32_t>(evt.state.X.rel);
    e._relative_y = static_cast<float32_t>(evt.state.Y.rel);

    _scene->OnMouseDown(e);

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuGameState::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{

    if (_camera_locked == false)
    {
        _camera_manager.injectMouseUp(evt, id);
        return true;
    }


    TileShell::Input::MouseEventArgs e;
    e._absolute_x = static_cast<float32_t>(evt.state.X.abs);
    e._absolute_y = static_cast<float32_t>(evt.state.Y.abs);
    e._buttons = evt.state.buttons;
    e._relative_x = static_cast<float32_t>(evt.state.X.rel);
    e._relative_y = static_cast<float32_t>(evt.state.Y.rel);

    _scene->OnMouseUp(e);

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuGameState::mouseMoved(const OIS::MouseEvent& evt)
{

    if (_camera_locked == false)
    {
        _camera_manager.injectMouseMove(evt);
        return true;
    }


    TileShell::Input::MouseEventArgs e;
    e._absolute_x = static_cast<float32_t>(evt.state.X.abs);
    e._absolute_y = static_cast<float32_t>(evt.state.Y.abs);
    e._buttons = evt.state.buttons;
    e._relative_x = static_cast<float32_t>(evt.state.X.rel);
    e._relative_y = static_cast<float32_t>(evt.state.Y.rel);

    _scene->OnMouseMove(e);

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuGameState::keyPressed(const OIS::KeyEvent& evt)
{
#if 0

    if (evt.key == OIS::KC_SPACE)
    {
        PushState(PlayGameState::getInstance());
    }

    if (evt.key == OIS::KC_ESCAPE)
    {
        _exit_game = true;
    }

#endif

    if (evt.key == OIS::KC_F12)
    {
        GameManager::getSingleton().SaveScreenShot();
    }

    if (evt.key == OIS::KC_F1)
    {
        _renderer.SetWireframe(!_renderer.GetWireframe());
    }

    //#ifdef _DEBUG
    if (evt.key == OIS::KC_F2)
    {
        _camera_locked = !_camera_locked;
    }

    //#endif

    //#ifdef _DEBUG

    if (_camera_locked == false)
    {
        _camera_manager.injectKeyDown(evt);
        return true;
    }

    //#endif

    TileShell::Input::KeyEventArgs e;
    e._text = evt.text;
    e._key = static_cast<TileShell::Input::KeyCode>(evt.key);

    _scene->OnKeyDown(e);
    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuGameState::keyReleased(const OIS::KeyEvent& evt)
{
    if (_camera_locked == false)
    {
        _camera_manager.injectKeyUp(evt);
        return true;
    }

    TileShell::Input::KeyEventArgs e;
    e._text = evt.text;
    e._key = static_cast<TileShell::Input::KeyCode>(evt.key);

    _scene->OnKeyUp(e);
    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuGameState::frameStarted(const Ogre::FrameEvent& evt)
{
    _ts_started = __rdtsc();

    if (_camera_locked == false)
    {
        _camera_manager.frameRenderingQueued(evt);
    }

    _scene->Update(evt.timeSinceLastFrame);

    TileShell::UI::MenuScene* scene = _scene.cast<TileShell::UI::MenuScene>();

    //#ifdef _DEBUG
    if (scene != nullptr && _camera_locked)
        //#else
        //  if (scene != nullptr)
        //#endif
    {
        //#if DEBUG
        Ogre::Camera* camera = _camera_manager.getCamera();
        //#else
        //        Ogre::Camera* camera = _camera;
        //#endif

        if (camera != nullptr)
        {
            TileShell::UI::Controls::ActivityCameraPlacement placement;
            scene->GetCameraPlacement(placement);

            Ogre::Vector3 position(placement._position.X, placement._position.Y, placement._position.Z);
            Ogre::Vector3 target(placement._target.X, placement._target.Y, placement._target.Z);
            Ogre::Vector3 dir_up(placement._up.X, placement._up.Y, placement._up.Z);
            dir_up.normalise();



            position.x *= 0.01F;
            position.y *= 0.01F;
            position.z *= 0.01F;
            target.x *= 0.01F;
            target.y *= 0.01F;
            target.z *= 0.01F;

            camera->setPosition(position);
            camera->lookAt(target);
            camera->setFixedYawAxis(true, dir_up);
        }
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuGameState::frameEnded(const Ogre::FrameEvent& evt)
{
    _ts_ended = __rdtsc();
    _ts_avg = static_cast<double>(_ts_ended - _ts_started) / static_cast<double>(_ts_persecond);

    if (_exit_game)
    {
        return false;
    }

    /*std::stringstream ss;
    ss << "draw calls: " << _renderer.GetDrawCalls() << ", vertex-count: " << _renderer.GetVertexCount() << "\n";
    ::OutputDebugStringA(ss.str().c_str());*/

    return true;
}
//------------------------------------------------------------------------------------------------//
bool MenuGameState::ReleaseResources()
{
    delete _mm_menu;
    delete _mm_menu_exit;
    delete _mm_options_video;
    delete _mm_options_audio;
    delete _mm_options_keybindings;
    delete _mm_options_gameplay;
    delete _mm_options_controls;

    _mm_menu                    = nullptr;
    _mm_menu_exit               = nullptr;
    _mm_options_video           = nullptr;
    _mm_options_audio           = nullptr;
    _mm_options_keybindings     = nullptr;
    _mm_options_gameplay        = nullptr;
    _mm_options_controls        = nullptr;

    _scene = nullptr;
    return GameState::ReleaseResources();
}
//------------------------------------------------------------------------------------------------//
}
//------------------------------------------------------------------------------------------------//
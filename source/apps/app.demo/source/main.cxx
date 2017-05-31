#include <Windows.h>
#include <core/Environment.hxx>
#include <core.Diagnostics/Trace.hxx>
#include <core.Diagnostics/Debug.hxx>
#include <core/CoreApplication.hxx>
#include <core/CoreWindow.hxx>
#include <core.Rendering/RenderSystem.hxx>
#include <core/Timer.hxx>
#include <core/FileSystem.hxx>
#include <algorithm>

#include <game.hxx>

extern "C" { __declspec(dllexport) ::DWORD NvOptimusEnablement = 0x00000001; }

#if defined(GRAPHYTE_PLATFORM_WINDOWS)
::INT WINAPI WinMain(::HINSTANCE hThisInstance, HINSTANCE hPrevInstance, ::LPSTR szCmdLine, ::INT nCmdLine)
#else
int main(int argc, char* argv[])
#endif
{
#if defined(GRAPHYTE_PLATFORM_WINDOWS)
    (void)hThisInstance;
    (void)hPrevInstance;
    (void)szCmdLine;
    (void)nCmdLine;
#else
    (void)argc;
    (void)argv;
#endif

    //
    // Initialize basic environment.
    //
    Core::Environment::Initialize(hThisInstance);
    {
        //
        // Run application framework.
        //
        auto application = Core::CoreApplication::MakeApplication();
        {
            //
            // Instantiate render system.
            //
            // Note:
            //
            //      This render system implementation is almost ready to be abstracted over
            //      more rendering APIs than Direct3D 11 used in this application.
            //
            auto renderSystem = Core::Rendering::RenderSystem::MakeRenderSystem();

            //
            // Instantiate game.
            //
            auto game = Core::MakeRef<GameProject::Game>();
            application->SetEventHandler(game);
            {

                //
                // Pump some messages: somehow my laptop didn't refreshed window content
                // until I clicked Alt+Enter to enter fullscreen.
                //
                Core::CoreApplication::PumpMessages();

                //
                // All systems working. Instantiate game.
                //
                game->Initialize();

                //
                // Start up timer.
                //
                Core::Timer timer{};
                timer.Start();

                //
                // Tick timer.
                //
                timer.Tick();

                //
                // Work until user requests exit.
                //
                while (!Core::Environment::IsExitRequested())
                {
                    //
                    // Tick timer.
                    //
                    timer.Tick();

                    //
                    // Compute current delta time.
                    //
                    auto deltaTime = timer.DeltaTime();

                    //
                    // Clamp it to sane range.
                    //
                    deltaTime = (std::min)((std::max)(0.0F, deltaTime), 0.05F);

                    //
                    // Update application.
                    //
                    application->Tick(deltaTime);

                    //
                    // And render system.
                    //
                    renderSystem->Tick(deltaTime);

                    //
                    // And game.
                    //
                    game->Tick(deltaTime);

                    //
                    // Render game objects.
                    //
                    game->Render(deltaTime);

                    //
                    // Pump messages.
                    //
                    Core::CoreApplication::PumpMessages();
                }

                //
                // Shutdown game.
                //
                game->Shutdown();
            }
        }
    }

    //
    // And basic environment.
    //
    Core::Environment::Shutdown();
    return 0;
}

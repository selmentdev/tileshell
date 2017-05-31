//
// Copyright (C) Selmentdev, 2017
//
//      See LICENSE file in the project root for full license information.
//

#include <game.hxx>
#include <core/environment.hxx>
#include <core/FileSystem.hxx>
#include <core/CoreApplication.hxx>
#include <core/StringFormat.hxx>

namespace GameProject
{
    using namespace Core;

    Game* Game::Current{ nullptr };

    Game::Game() noexcept
    {
        CORE_ASSERT(Game::Current == nullptr);
        Game::Current = this;
        ::ShowCursor(FALSE);
    }

    Game::~Game() noexcept
    {
        CORE_ASSERT(Game::Current == this);
        Game::Current = nullptr;
    }

    void Game::OnWindowClose(CoreWindow* window) noexcept
    {
        (void)window;
        Environment::RequestExit();
    }


    bool Game::OnKeyDown(uint32_t keyCode, char32_t character, bool isRepeat) noexcept
    {
        (void)isRepeat;
        (void)keyCode;
        (void)character;
        return true;
    }

    bool Game::OnKeyUp(uint32_t keyCode, char32_t character, bool isRepeat) noexcept
    {
        (void)isRepeat;
        (void)keyCode;
        (void)character;
        return true;
    }

    bool Game::OnWindowSizeChanged(CoreWindow* window, int32_t width, int32_t height, bool wasMinimized) noexcept
    {
        (void)window;
        (void)wasMinimized;

        if (m_Viewport != nullptr)
        {
            Rendering::RenderSystem::Current->ResizeViewport(m_Viewport, width, height, false);
        }

        return true;
    }

    bool Game::OnWindowActivated(CoreWindow* window, CoreWindowActivation activationType) noexcept
    {
        (void)window;
        (void)activationType;
        return true;
    }

    bool Game::OnApplicationActivated(bool isActive) noexcept
    {
        (void)isActive;
        return true;
    }

    bool Game::OnWindowEnterSizeMove(CoreWindow* window) noexcept
    {
        (void)window;
        return true;
    }

    void Game::OnWindowExitSizeMove(CoreWindow* window) noexcept
    {
        (void)window;
    }

    void Game::Tick(float deltaTime) noexcept
    {
        (void)deltaTime;
    }

    void Game::Render(float deltaTime) noexcept
    {
        (void)deltaTime;
        auto renderSystem = Rendering::RenderSystem::Current;

        //
        // Prepare rendering to viewport.
        //
        renderSystem->BeginDrawViewport(m_Viewport);

        //
        // Do actual render.
        //
        (void)deltaTime;
        auto commandList = renderSystem->GetImmediateCommandList();

        //
        // Present & flip.
        //
        renderSystem->EndDrawViewport(m_Viewport, true, 1);
    }

    void Game::Restart() noexcept
    {
    }

    void Game::NotifyMeteoriteShotDown() noexcept
    {
    }

    void Game::DoRestart() noexcept
    {
    }

    void Game::RecomputeInterval() noexcept
    {
    }

    void Game::Initialize() noexcept
    {
        auto application = CoreApplication::Current;
        auto renderSystem = Rendering::RenderSystem::Current;

        //
        // Instantiate window.
        // 
        CoreWindowDesc desc{};
        desc.Width = 1280;
        desc.Height = 720;

        m_Window = application->MakeWindow(desc);
        m_Window->Show();

        //
        // Make viewport for allocated window.
        //
        m_Viewport = renderSystem->MakeViewport(m_Window->GetHandle(), desc.Width, desc.Height, false);
    }

    void Game::Shutdown() noexcept
    {
        m_Viewport = nullptr;

        m_Window->Destroy();
        m_Window = nullptr;
    }

    DirectX::XMVECTOR XM_CALLCONV Game::RandomVector2D() noexcept
    {
        DirectX::XMFLOAT2A result;

        std::uniform_real<float> distribution{};

        result.x = distribution(m_RandomEngine);
        result.y = distribution(m_RandomEngine);

        return DirectX::XMVector2Normalize(DirectX::XMLoadFloat2A(&result));
    }

    DirectX::XMVECTOR XM_CALLCONV Game::RandomVector3D() noexcept
    {
        DirectX::XMFLOAT3A result;

        std::uniform_real<float> distribution{};

        result.x = distribution(m_RandomEngine);
        result.y = distribution(m_RandomEngine);
        result.z = distribution(m_RandomEngine);

        return DirectX::XMVector3Normalize(DirectX::XMLoadFloat3A(&result));
    }

    DirectX::XMVECTOR XM_CALLCONV Game::RandomVector3D(DirectX::FXMVECTOR min, DirectX::FXMVECTOR max) noexcept
    {
        DirectX::XMFLOAT3A vmin;
        DirectX::XMFLOAT3A vmax;

        DirectX::XMStoreFloat3A(&vmin, min);
        DirectX::XMStoreFloat3A(&vmax, max);

        std::uniform_real<float> distributionX{ vmin.x, vmax.x };
        std::uniform_real<float> distributionY{ vmin.y, vmax.y };
        std::uniform_real<float> distributionZ{ vmin.z, vmax.z };

        DirectX::XMFLOAT3A result;
        result.x = distributionX(m_RandomEngine);
        result.y = distributionY(m_RandomEngine);
        result.z = distributionZ(m_RandomEngine);

        return DirectX::XMLoadFloat3A(&result);
    }

    DirectX::XMVECTOR XM_CALLCONV Game::RandomUnitVector() noexcept
    {
        std::uniform_real<float> uniform{};

        //
        // Compute random `signum` for target axis vector.
        //
        auto signum = (uniform(m_RandomEngine) > 0.5F) ? 1.0F : -1.0F;

        DirectX::XMFLOAT3A axis;
        axis.x = uniform(m_RandomEngine);
        axis.y = uniform(m_RandomEngine);

        //
        // Square known two components.
        //
        const auto x2 = axis.x * axis.x;
        const auto y2 = axis.y * axis.y;

        //
        // And final z component.
        //
        axis.z = signum * std::sqrt(1.0F - x2 - y2);

        const auto result = DirectX::XMLoadFloat3A(&axis);
        return result;
    }

    DirectX::XMVECTOR XM_CALLCONV Game::RandomQuaternion() noexcept
    {
        std::uniform_real<float> uniform{};
        std::uniform_real<float> randomAngle{ 0.0F, DirectX::XM_2PI };


        //
        // Compute random angle.
        //
        const auto angle = randomAngle(m_RandomEngine);

        //
        // And random axis.
        //
        const auto axis = RandomUnitVector();

        //
        // And create quaternion from it.
        //
        const auto result = DirectX::XMQuaternionRotationAxis(axis, angle);
        return result;
    }

    DirectX::XMVECTOR XM_CALLCONV Game::RandomAngularVelocity(float max) noexcept
    {
        std::uniform_real<float> uniform{};

        DirectX::XMFLOAT3A vector;
        vector.x = uniform(m_RandomEngine);
        vector.y = uniform(m_RandomEngine);
        vector.z = uniform(m_RandomEngine);

        const auto result = DirectX::XMVectorScale(DirectX::XMLoadFloat3A(&vector), max);
        return result;
    }

    float Game::RandomScalar(float min, float max) noexcept
    {
        std::uniform_real<float> distribution{ min, max };
        return distribution(m_RandomEngine);
    }
}
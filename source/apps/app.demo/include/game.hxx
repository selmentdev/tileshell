#ifndef INCLUDED_GAME_HXX
#define INCLUDED_GAME_HXX

//
// Copyright (C) Selmentdev, 2017
//
//      See LICENSE file in the project root for full license information.
//

#include <core/CoreEventHandler.hxx>
#include <core/CoreWindow.hxx>
#include <core.World/Scene.hxx>
#include <core.Rendering/CommandList.hxx>
#include <core.Rendering/RenderSystem.hxx>

#include <core.Rendering/MaterialRenderer.hxx>
#include <core.Rendering/MeshRenderer.hxx>
#include <core.World/Camera.hxx>


#include <random>

namespace GameProject
{
    using namespace Core;

    class Game : public CoreEventHandler
    {
    public:
        static Game* Current;

    private:
        CoreWindowRef m_Window;
        Rendering::ViewportRef m_Viewport;

    public:
        static constexpr const auto VisibleRangeExtent = 20.0F;

    private:
        std::mt19937 m_RandomEngine;

    public:
        Game() noexcept;
        virtual ~Game() noexcept;

    public:
        virtual void OnWindowClose(CoreWindow* window) noexcept override final;
        virtual bool OnKeyDown(uint32_t keyCode, char32_t character, bool isRepeat) noexcept override final;
        virtual bool OnKeyUp(uint32_t keyCode, char32_t character, bool isRepeat) noexcept override final;

        virtual bool OnWindowSizeChanged(CoreWindow* window, int32_t width, int32_t height, bool wasMinimized) noexcept override final;
        virtual bool OnWindowActivated(CoreWindow* window, CoreWindowActivation activationType) noexcept override final;
        virtual bool OnApplicationActivated(bool isActive) noexcept override final;
        virtual bool OnWindowEnterSizeMove(CoreWindow* window) noexcept override final;
        virtual void OnWindowExitSizeMove(CoreWindow* window) noexcept override final;

        virtual void Tick(float deltaTime) noexcept;
        virtual void Render(float deltaTime) noexcept;

    public:
        void Restart() noexcept;
        void NotifyMeteoriteShotDown() noexcept;

    private:
        void DoRestart() noexcept;
        void RecomputeInterval() noexcept;

    public:
        virtual void Initialize() noexcept;
        virtual void Shutdown() noexcept;

    private:
        DirectX::XMVECTOR XM_CALLCONV RandomVector2D() noexcept;
        DirectX::XMVECTOR XM_CALLCONV RandomVector3D() noexcept;
        DirectX::XMVECTOR XM_CALLCONV RandomVector3D(DirectX::FXMVECTOR min, DirectX::FXMVECTOR max) noexcept;
        DirectX::XMVECTOR XM_CALLCONV RandomUnitVector() noexcept;
        DirectX::XMVECTOR XM_CALLCONV RandomQuaternion() noexcept;
        DirectX::XMVECTOR XM_CALLCONV RandomAngularVelocity(float max) noexcept;

        float RandomScalar(float min, float max) noexcept;
    };
}
#endif // INCLUDED_GAME_HXX
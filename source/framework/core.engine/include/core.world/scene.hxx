#ifndef INCLUDED_CORE_WORLD_SCENE_HXX
#define INCLUDED_CORE_WORLD_SCENE_HXX

//
// Copyright (C) Selmentdev, 2017
//
//      See LICENSE file in the project root for full license information.
//

#include <core/common.hxx>
#include <core/reference.hxx>
#include <core.world/gameobject.hxx>
#include <core.world/camera.hxx>

namespace Core::World
{
    using SceneRef = Reference<class Scene>;
    class Scene : public Object
    {
        friend class Physics;

    private:
        static constexpr const float FixedDeltaTime = 0.02F;

    private:
        //
        // Scene params for GPU.
        //
        // Note:
        //      Currently 32bit build is not supported.
        //
        //      It might be when **someone** will implement aligned new / delete for certain classes
        //      **OR** we get C++17 aligned new in MSVS :)
        //
        //      http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0035r4.html
        //
        struct SceneParams
        {
            DirectX::XMFLOAT4X4A World;
            DirectX::XMFLOAT4X4A InverseWorld;
        };
        static_assert(alignof(SceneParams) >= alignof(DirectX::XMVECTOR), "");

    private:
        std::vector<GameObjectRef> m_Objects;

        Core::World::CameraRef m_Camera;
        Core::Rendering::UniformBufferRef m_CurrentObject;

        SceneParams m_SceneParams;

    public:
        Scene() noexcept;
        virtual ~Scene() noexcept;

    public:
        Core::World::CameraRef GetCamera() const noexcept
        {
            return m_Camera;
        }

        size_t GetObjectsCount() const noexcept
        {
            return m_Objects.size();
        }

        void Clear() noexcept;

    private:
        void RenderSingleObject(const World::GameObjectRef& gameObject, const Rendering::CommandListRef& commandList) noexcept;

    public:
        void OnUpdate(float deltaTime) noexcept;
        void OnRender(const Rendering::CommandListRef& commandList) noexcept;

    public:
        void Add(const GameObjectRef& gameObject) noexcept;
        void Remove(const GameObjectRef& gameObject) noexcept;
        void Tick(float deltaTime) noexcept;

    private:
        void RemovePendingObjects() noexcept;
    };
}

#endif // INCLUDED_CORE_WORLD_SCENE_HXX

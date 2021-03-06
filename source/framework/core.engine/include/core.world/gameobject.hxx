#ifndef INCLUDED_CORE_WORLD_GAMEOBJECT_HXX
#define INCLUDED_CORE_WORLD_GAMEOBJECT_HXX

//
// Copyright (C) Selmentdev, 2017
//
//      See LICENSE file in the project root for full license information.
//

#include <core/reference.hxx>
#include <core.rendering/commandlist.hxx>
#include <core/stringhash.hxx>

namespace Core::World
{
    using GameObjectID = uint32_t;
    using GameObjectTypeID = uint32_t;

    using GameObjectRef = Reference<class GameObject>;
    class GameObject : public Object
    {
        friend class Scene;
    protected:
        const GameObjectTypeID TypeID;

    private:
        bool m_MarkedToRemove;

    public:
        GameObject(GameObjectTypeID typeID) noexcept;
        virtual ~GameObject() noexcept;

    public:
        virtual void OnUpdate(float deltaTime) noexcept;
        virtual void OnRender(const Rendering::CommandListRef& commandList) noexcept;
        virtual void OnCollision(GameObject* other) noexcept;

    public:
        void Destroy() noexcept
        {
            m_MarkedToRemove = true;
        }

    public:
        //
        // "Convenient" property :)
        //
        virtual DirectX::XMMATRIX XM_CALLCONV GetTransform() const noexcept;
        DirectX::XMVECTOR XM_CALLCONV GetPosition() const noexcept;
        bool IsMarkedToRemove() const noexcept
        {
            return m_MarkedToRemove;
        }
    };
}

#endif // INCLUDED_CORE_WORLD_GAMEOBJECT_HXX
//
// Copyright (C) Selmentdev, 2017
//
//      See LICENSE file in the project root for full license information.
//

#include <Core.World/GameObject.hxx>

namespace Core::World
{
    GameObject::GameObject(GameObjectTypeID typeID) noexcept
        : TypeID{ typeID }
        , m_MarkedToRemove{ false }
    {
    }

    GameObject::~GameObject() noexcept
    {
    }

    void GameObject::OnUpdate(float deltaTime) noexcept
    {
        (void)deltaTime;
    }

    void GameObject::OnRender(const Rendering::CommandListRef& commandList) noexcept
    {
        (void)commandList;
    }

    DirectX::XMMATRIX XM_CALLCONV GameObject::GetTransform() const noexcept
    {
        return DirectX::XMMatrixIdentity();
    }

    DirectX::XMVECTOR XM_CALLCONV GameObject::GetPosition() const noexcept
    {
        return DirectX::XMVectorZero();
    }

    void GameObject::OnCollision(GameObject* other) noexcept
    {
        (void)other;
    }
}
//
// Copyright (C) Selmentdev, 2017
//
//      See LICENSE file in the project root for full license information.
//

#include <core.world/scene.hxx>
#include <core.diagnostics/trace.hxx>
#include <core.rendering/rendersystem.hxx>


namespace Core::World
{
    Scene::Scene() noexcept
    {
        //
        // Allocate new camera.
        //
        m_Camera = Core::MakeRef<Core::World::Camera>();

        //
        // Allocate uniform buffer for scene data.
        //
        m_CurrentObject = Core::Rendering::RenderSystem::Current->MakeUniformBuffer(Rendering::BufferDesc{ m_SceneParams });
        CORE_TRACE_MESSAGE(Debug, "[SCENE] Creating scene");
    }

    Scene::~Scene() noexcept
    {
        CORE_TRACE_MESSAGE(Debug, "[SCENE] Destroying scene");
    }

    void Scene::RenderSingleObject(const World::GameObjectRef& gameObject, const Rendering::CommandListRef& commandList) noexcept
    {
        //
        // Get world transform matrix.
        //
        auto world = gameObject->GetTransform();

        //
        // Store it in scene params.
        //
        DirectX::XMStoreFloat4x4A(&m_SceneParams.World, world);
        DirectX::XMStoreFloat4x4A(&m_SceneParams.InverseWorld, DirectX::XMMatrixTranspose(world));

        //
        // Update GPU buffer with scene object params.
        //
        commandList->UpdateUniformBuffer(m_CurrentObject, &m_SceneParams, sizeof(m_SceneParams));

        //
        // Render actual mesh of game object.
        //
        gameObject->OnRender(commandList);
    }

    void Scene::OnUpdate(float deltaTime) noexcept
    {
        //
        // Update all game objects.
        //
        for (auto& gameObject : m_Objects)
        {
            gameObject->OnUpdate(deltaTime);
        }
    }

    void Scene::OnRender(const Rendering::CommandListRef& commandList) noexcept
    {
        //
        // Bind uniform buffer with object data.
        //
        commandList->BindUniformBuffer(Core::Rendering::ShaderMask::Vertex, 1, m_CurrentObject);

        //
        // Bind any camera resources.
        //
        m_Camera->Bind(commandList);

        //
        // Apply rendering to all objects on scene.
        //
        for (auto& gameObject : m_Objects)
        {
            RenderSingleObject(gameObject, commandList);
        }
    }

    void Scene::Add(const GameObjectRef& gameObject) noexcept
    {
        //
        // Sanity check.
        //
        CORE_ASSERT(gameObject != nullptr);

        //
        // Check if object isn't at list already.
        //
        CORE_ASSERT(std::find(std::begin(m_Objects), std::end(m_Objects), gameObject) == std::end(m_Objects));

        //
        // Fine, push it back to list.
        //
        m_Objects.push_back(gameObject);
    }

    void Scene::Remove(const GameObjectRef& gameObject) noexcept
    {
        //
        // Sanity check.
        //
        CORE_ASSERT(gameObject != nullptr);

        //
        // Make sure that object is on scene.
        //
        CORE_ASSERT(std::find(std::begin(m_Objects), std::end(m_Objects), gameObject) != std::end(m_Objects));

        //
        // Just mark object to be removed.
        //
        gameObject->Destroy();
    }

    void Scene::Tick(float deltaTime) noexcept
    {
        //
        // Update physics with fixed delta time step.
        //
        auto delta = deltaTime;
        while (delta >= 0.0F)
        {
            //
            // Try to remove pending objects.
            //
            RemovePendingObjects();

            //
            // Update counter.
            //
            delta -= FixedDeltaTime;
        }
    }

    void Scene::RemovePendingObjects() noexcept
    {
        //
        // Capture range.
        //
        auto begin = std::begin(m_Objects);
        auto end = std::end(m_Objects);

        //
        // Remove and compact items on scene.
        //
        auto it = std::remove_if(begin, end, [&](auto o) -> bool
        {
            if (o->IsMarkedToRemove())
            {
                return true;
            }
            return false;
        });

        //
        // Erase removed items slots.
        //
        m_Objects.erase(it, end);
    }

    void Scene::Clear() noexcept
    {
        //
        // Destroy all objects in scene.
        //
        for (auto& go : m_Objects)
        {
            go->Destroy();
        }

        //
        // Force to remove pending objects.
        //
        // Previous step will just mark objects as destroyed.
        //
        RemovePendingObjects();
    }
}
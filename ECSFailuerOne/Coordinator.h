#pragma once

#include "JMemory.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "System.h"

#include <assert.h>

class Coordinator {
public:
    void Init() {
        // Create pointers to each manager
        m_ComponentManager = new ComponentManager();
        m_EntityManager = new EntityManager();
        m_SystemManager = new SystemManager();
    }

    Entity* CreateEntity() {
        return m_EntityManager->CreateEntity();
    }

    void DestroyEntity(Entity* entity) {
        m_EntityManager->DestroyEntity(entity);

        m_ComponentManger->DestroyEntity(entity);

        m_SystemManager->DestroyEntity(entity);
    }

    // Component methods
    template<typename T>
    void RegisterComponent() {
        m_ComponentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity* entity, T component) {
        m_ComponentManager->AddComponent<T>(entity, component);

        auto signature = m_EntityManager->GetSignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), true);
        m_EntityManager->SetSignature(entity, signature);

        m_SystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void RemoveComponent(Entity* entity) {
        m_ComponentManager->RemoveComponent<T>(entity);

        auto signature = m_EntityManager->GetSignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), false);
        m_EntityManager->SetSignature(entity, signature);

        m_SystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& GetComponent(Entity* entity) {
        return m_ComponentManager->GetComponent<T>(entity);
    }


    // System methods
    template<typename T>
    T* RegisterSystem() {
        return m_SystemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature) {
        m_SystemManager->SetSignature<T>(signature);
    }

private:
    ComponentManager* m_ComponentManager;
    EntityManager* m_EntityManager;
    SystemManager* m_SystemManager;
}
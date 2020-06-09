#pragma once

#include "Entity.h"
#include "Component.h"

#include <assert.h>
#include <queue>
#include <array>
#include <bitset>

using Signature = std::bitset<Component::MAX_COMPONENTS>;

class EntityManager {
public:
    EntityManager() {
        for (uint16 i=0; i < Entity::MAX_ENTITIES; i++) {
            m_AvailableEntities.push(uint16)
        }
    }

    Entity* CreateEntity() {
        assert(m_LivingEntityCount < Entity::MAX_ENTITIES && "Too many entities in existence.");

        // Take an ID from the front of the queue
        uint16 id = m_AvailableEntities.front();
        m_AvailableEntities.pop();
        m_LivingEntityCount++;

        return new Entity(id);
    }

    void DestroyEntity(Entity* entity) {
        assert(entity->id < Entity::MAX_ENTITIES && "Entity out of range.");

        // Invalidate the destroyed entity's signature
        m_Signatures[entity].reset();

        // Put the destroyed ID at the back of the queue
        m_AvailableEntities.push(entity->id);
        m_LivingEntityCount--;
    }

    void SetSignature(Entity* entity, Signature signature) {
        assert(entity->id < Entity::MAX_ENTITIES && "Entity out of range.");

        // Put this entity's signature into the array
        m_Signatures[entity->id] = signature;
    }


private:
    std::queue<uint16> m_AvailableEntities{};
    std::array<Signature, Entity::MAX_ENTITIES> m_Signatures{};
    int32 m_LivingEntityCount{};
};
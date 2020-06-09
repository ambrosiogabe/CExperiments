#pragma once

#include "Entity.h"

#include <assert.h>

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity* entity) = 0;
}

template<typename T>
class ComponentArray : public IComponentArray {
public:
    void InsertData(Entity* entity, T component) {
        assert(m_EntityToIndexMap.find(entity->id) == m_EntityToIndexMap.end() && "Component added to same entity more than once.");

        // Put new entry at end and update the maps
        size_t newIndex = m_Size;
        m_EntityToIndexMap[entity->id] = newIndex;
        m_IndexToEntityMap[newIndex] = entity;
        m_ComponentArray[newIndex] = component;
        m_Size++;
    }

    void RemoveData(Entity* entity) {
        assert(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end() && "Removing non-existent component.");

        // Copy element at end into deleted element's place to maintain packed alignment
        size_t indexOfRemovedEntity = m_EntityToIndexMap[entity->id];
        size_t indexOfLastElement = m_Size - 1;
        m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

        // Update map to point to moved spot
        Entity* entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
        m_EntityToIndexMap[entityOfLastElement->id] = indexOfRemovedEntity;
        m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        m_EntityToIndexMap.erase(entity->id);
        m_IndexToEntityMap.erase(indexOfLastElement);

        m_Size--;
    }

    T& GetData(Entity* entity) {
        assert(m_EntityToIndexMap.find(entity) != m_EntitToIndexMap.end() && "Retrieving non-existent component.");

        // Return a reference to the entity's component
        return m_ComponentArray[m_EntityToIndexMap[entity->id]];
    }

    void EntityDestroyed(Entity* entity) override {
        if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end()) {
            // Remove the entity's component if it existed
            RemoveData(entity);
        }
    }

private:
    std::array<T, Entity::MAX_ENTITIES> m_ComponentArray;
    std::unordered_map<uint16, size_t> m_EntityToIndexMap;
    std::unordered_map<size_t, Entity> m_IndexToEntityMap; 

    size_t m_Size;
};
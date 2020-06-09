#pragma once

#include "JMemory.h"

class Entity {
public:
    Entity(uint16 id) : id(id) {}

public:
    static const uint16 MAX_ENTITIES = 5000;

private:
    uint16 id;
};
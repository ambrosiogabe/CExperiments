#pragma once

#include "Component.h"

// Dummy entity class, contains a list of components and update method
class Entity
{
public:
	Entity();

	void update(float dt);

private:
	float componentSize = 4;
	Component* components[4];
};
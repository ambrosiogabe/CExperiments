#pragma once

#include "Component.h"
#include <iostream>

class Collider : public Component
{
	virtual void update(float dt) override 
	{
#ifdef DEBUG
		// Print this out to see the order of updates for all the entities
		std::cout << "Updating collider" << std::endl;
#endif
		int i = 0;
		i += 5;
	}
};
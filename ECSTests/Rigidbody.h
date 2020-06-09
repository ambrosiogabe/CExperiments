#pragma once

#include "Component.h"
#include <iostream>

class Rigidbody : public Component
{
	virtual void update(float dt) override
	{
#ifdef DEBUG
		// Print this out to see the order of updates for all the entities
		std::cout << "Updating rigidbody" << std::endl;
#endif
		int i = 0;
		i += 35;
		float d = dt * 0.1f;
		d *= 0.3f;
	}
};
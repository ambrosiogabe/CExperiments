#pragma once

#include "Component.h"
#include <iostream>

class SpriteRenderer : public Component
{
	virtual void update(float dt) override
	{
#ifdef DEBUG
		// Print this out to see the order of updates for all the entities
		std::cout << "Updating sprite renderer" << std::endl;
#endif
		int i = 0;
		i += 10;
		i -= 5;
		float b = dt * 0.24f;
	}
};
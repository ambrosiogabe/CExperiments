#pragma once

#include "Component.h"
#include <iostream>

class FontRenderer : public Component
{
	virtual void update(float dt) override
	{
#ifdef DEBUG
		// Print this out to see the order of updates for all the entities
		std::cout << "Updating font renderer" << std::endl;
#endif
		int i = 0;
		i += 23034;
	}
};
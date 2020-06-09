#pragma once


// Abstract component class with virtual update
class Component
{
public:
	virtual void update(float dt) = 0;
};
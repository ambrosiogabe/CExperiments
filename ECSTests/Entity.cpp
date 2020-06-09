
#include "Collider.h"
#include "FontRenderer.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"
#include "Entity.h"

Entity::Entity()
{
	components[0] = new Collider();
	components[1] = new FontRenderer();
	components[2] = new Rigidbody();
	components[3] = new SpriteRenderer();
}

void Entity::update(float dt)
{
	for (int i=0; i < componentSize; i++)
	{
		Component* component = components[i];
		component->update(dt);
	}
}
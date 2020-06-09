#include <iostream>
#include "FontRenderer.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "Entity.h"

#include <chrono>
using namespace std::chrono;

int main()
{
	// The amount of frames to run for at a simulated 60 FPS
	// (lower this number to get a faster test)
	int testSize = 108000;

	// The amount of entities in the test group
	int entitySize = 10000;

	// ===================================================================================
	// Non ECS -- This uses the typical Component Pattern approach
	// and literally places the GameObject's and Entities anywhere
	// in memory that is available
	// ===================================================================================

	// Initialize the entities, each gets 4 components
	Entity** entities = new Entity*[entitySize];
	for (int i = 0; i < entitySize; i++)
	{
		entities[i] = new Entity();
	}

	// Run the update loop for the amount of frames (testSize) and
	// record the average time it takes to update all entities
	float avgMicroSecond = 0.0f;
	for (int i = 0; i < testSize; i++)
	{
		auto start = high_resolution_clock::now();
		for (int i = 0; i < entitySize; i++)
		{
			entities[i]->update(1.0f / 60.0f);
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		avgMicroSecond += duration.count();
	}
	std::cout << "Average total Entity update time: " << avgMicroSecond / testSize << " us" << std::endl;
	avgMicroSecond = 0.0f;


	// ===================================================================================
	// ECS -- This chunk allocates the memory so that components are
	// right next to each other (e.g)
	//		collider, collider, ..., rigidbody, rigidbody, ... , ...
	// Then runs through the memory and updates each block of memory
	// consecutively.
	// ===================================================================================

	// Allocate 100 Mb of void memory to play with
	void* memory = malloc(1000000 * 100);
	void* memoryPtr = memory;
	
	// Place 4 components for every entity into the memory space
	// so that they are right next to each other (this could probably
	// be done better, I'm not an advanced user of C++)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < entitySize; j++)
		{
			if (i == 0)
			{
				Collider* memAddress = new(memoryPtr) Collider();
				memAddress++;
				memoryPtr = (void*)memAddress;
			}
			else if (i == 1)
			{
				Rigidbody* memAddress = new(memoryPtr) Rigidbody();
				memAddress++;
				memoryPtr = (void*)memAddress;
			}
			else if (i == 2)
			{
				SpriteRenderer* memAddress = new(memoryPtr) SpriteRenderer();
				memAddress++;
				memoryPtr = (void*)memAddress;
			}
			else if (i == 3)
			{
				FontRenderer* memAddress = new(memoryPtr) FontRenderer();
				memAddress++;
				memoryPtr = (void*)memAddress;
			}
		}
	}

	// Loop through for the amount of frames, and record the amount of time
	// it takes to update every entity (via updating the components)
	for (int i = 0; i < testSize; i++)
	{
		auto start = high_resolution_clock::now();
		memoryPtr = memory;
		for (int component = 0; component < 4; component++)
		{
			Component* comp;
			if (component == 0)
			{
				comp = (Collider*)memoryPtr;
			}
			else if (component == 1)
			{
				comp = (Rigidbody*)memoryPtr;
			}
			else if (component == 2)
			{
				comp = (SpriteRenderer*)memoryPtr;
			}
			else
			{
				comp = (FontRenderer*)memoryPtr;
			}

		
			for (int entity = 0; entity < entitySize; entity++)
			{
				comp->update(1.0f / 60.0f);
				comp++;
			}
			memoryPtr = (void*)comp;
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		avgMicroSecond += duration.count();
	}
	std::cout << "Average total Entity update time taken by ECS: " << avgMicroSecond / testSize << " us" << std::endl;


	return 0;
}
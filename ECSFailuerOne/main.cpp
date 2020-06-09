#include "Entity.h"
#include "Coordinator.h"

#include <stdio.h>

struct Gravity 
{
    float force;
};

struct Rigidbody
{
    float velocity;
    float acceleration;
};

struct Transform 
{
    float position;
    float rotation;
    float scale;
};

Coordinator gCoordinator;

int main() {
    gCoordinator.Init();

    gCoordinator.RegisterComponent<Gravity>();
    gCoordinator.RegisterComponent<Rigidbody>();
    gCoordinator.RegisterComponent<Transform>();

    Signature signature;

    return 0;
}
#ifndef Zoxel_Inputs
#define Zoxel_Inputs

// Data
#include "Data/PhysicalButton.c"
#include "Components/Keyboard.c"
#include "Tags/Device.c"
// Systems
#include "Systems/KeyboardExtractSystem.c"
#include "Systems/BobSpawnSystem.c"     // testing

void InitializeInputs(ecs_world_t *world)
{
    // Data
    ECS_COMPONENT(world, Keyboard);
    // Systems
    SpawnKeyboadEntity(world);
    InitializeBobSpawnSystem(world);
    ECS_SYSTEM(world, BobSpawnSystem, EcsOnUpdate, Keyboard);
}

#endif
#ifndef Zoxel_Inputs
#define Zoxel_Inputs

// Data
#include "Data/PhysicalButton.c"
#include "Components/Keyboard.c"
#include "Tags/Device.c"
// Declare Data
ECS_COMPONENT_DECLARE(Keyboard);
// Systems
#include "Systems/KeyboardExtractSystem.c"

void InputsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Inputs);
    ECS_COMPONENT_DEFINE(world, Keyboard);
}

#endif
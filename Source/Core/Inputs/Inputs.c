#ifndef Zoxel_Inputs
#define Zoxel_Inputs

// Tags
ECS_DECLARE(Device);
// Data
#include "Data/PhysicalButton.c"
// Components
#include "Components/Keyboard.c"
// Systems
#include "Systems/KeyboardExtractSystem.c"

void InputsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Inputs);
    ECS_TAG_DEFINE(world, Device);
    ECS_COMPONENT_DEFINE(world, Keyboard);
}
#endif
#ifndef Zoxel_Inputs
#define Zoxel_Inputs

// Tags
ECS_DECLARE(Device);
// data
#include "data/PhysicalButton.c"
// components
#include "components/Keyboard.c"
#include "components/Mouse.c"
// systems
#include "systems/KeyboardExtractSystem.c"
#include "systems/MouseExtractSystem.c"

void InputsImport(ecs_world_t *world)
{
    ECS_MODULE(world, inputs);
    ECS_TAG_DEFINE(world, Device);
    ECS_COMPONENT_DEFINE(world, Keyboard);
    ECS_COMPONENT_DEFINE(world, Mouse);
}

void ResetDevices(ecs_world_t *world)
{
    ResetKeyboard(world);
    ResetMouse(world);
}
#endif
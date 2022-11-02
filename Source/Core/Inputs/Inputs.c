#ifndef Zoxel_Inputs
#define Zoxel_Inputs

// Tags
ECS_DECLARE(Device);
// Data
#include "Data/PhysicalButton.c"
// Components
#include "Components/Keyboard.c"
#include "Components/Mouse.c"
// Systems
#include "Systems/KeyboardExtractSystem.c"
#include "Systems/MouseExtractSystem.c"

void InputsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Inputs);
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
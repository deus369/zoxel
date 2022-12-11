#ifndef zoxel_inputs
#define zoxel_inputs

// Tags
ECS_DECLARE(Device);
// data
#include "data/finger.c"
#include "data/physical_button.c"
// components
#include "components/gamepad.c"
#include "components/keyboard.c"
#include "components/mouse.c"
#include "components/touchscreen.c"
// prefabs
#include "prefabs/mouse.c"
// systems
#include "systems/keyboard_reset_system.c"
#include "systems/keyboard_extract_system.c"
#include "systems/mouse_extract_system.c"
#include "systems/mouse_raycaster_system.c"
#include "systems/dragger_end_system.c"
// util
#include "util/input_util.c"

//! Inputs system handles virtual devices.
/**
*   \todo Add Extract systems to mainthread
*/
void InputsImport(ecs_world_t *world)
{
    ECS_MODULE(world, inputs);
    ECS_TAG_DEFINE(world, Device);
    ECS_COMPONENT_DEFINE(world, Gamepad);
    ECS_COMPONENT_DEFINE(world, Keyboard);
    ECS_COMPONENT_DEFINE(world, Mouse);
    ECS_COMPONENT_DEFINE(world, Touchscreen);
    zoxel_system(world, MouseRaycasterSystem, EcsOnUpdate, [in] Mouse, [out] Raycaster);
    zoxel_system(world, DraggerEndSystem, EcsOnLoad, [out] DragableState, [out] DraggerLink, [out] DraggingDelta);
    spawn_prefab_mouse(world);
}
#endif
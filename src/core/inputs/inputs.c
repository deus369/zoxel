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
// systems
#include "systems/keyboard_extract_system.c"
#include "systems/mouse_extract_system.c"


void input_extract_from_sdl(ecs_world_t *world, SDL_Event event)
{
    ExtractKeyboard(world, event);
    ExtractMouseEvent(world, event);
}

void reset_input_devices(ecs_world_t *world)
{
    ResetKeyboard(world);
    ResetMouse(world);
}

void InputsImport(ecs_world_t *world)
{
    ECS_MODULE(world, inputs);
    ECS_TAG_DEFINE(world, Device);
    ECS_COMPONENT_DEFINE(world, Gamepad);
    ECS_COMPONENT_DEFINE(world, Keyboard);
    ECS_COMPONENT_DEFINE(world, Mouse);
    ECS_COMPONENT_DEFINE(world, Touchscreen);
    //! \todo Add Extract systems to mainthread
}
#endif
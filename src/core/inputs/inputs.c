#ifndef zoxel_inputs
#define zoxel_inputs

zoxel_declare_tag(Device)
#include "data/finger.c"
#include "data/physical_button.c"
#include "data/physical_stick.c"
#include "components/keyboard.c"
#include "components/mouse.c"
#include "components/gamepad.c"
#include "components/touchscreen.c"
#include "prefabs/mouse.c"
#include "prefabs/keyboard.c"
#include "prefabs/gamepad.c"
#include "systems/keyboard_reset_system.c"
#include "systems/keyboard_extract_system.c"
#include "systems/mouse_extract_system.c"
#include "systems/mouse_raycaster_system.c"
#include "systems/dragger_end_system.c"
#include "util/gamepad_util.c"
#include "util/input_util.c"

zoxel_begin_module(Inputs)
zoxel_define_tag(Device)
zoxel_define_component(Keyboard)
zoxel_define_component(Mouse)
zoxel_define_component(Gamepad)
zoxel_define_component(Touchscreen)
zoxel_system(MouseRaycasterSystem, EcsOnUpdate, [in] Mouse, [out] Raycaster)
zoxel_system(DraggerEndSystem, EcsOnLoad, [out] DragableState, [out] DraggerLink, [out] DraggingDelta)
spawn_prefab_mouse(world);
spawn_prefab_gamepad(world);
initialize_sdl_gamepads();
zoxel_end_module(Inputs)

// \todo Add Extract systems to mainthread

#endif
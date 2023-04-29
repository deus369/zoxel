#ifndef zoxel_inputs
#define zoxel_inputs

#include "data/finger.c"
#include "data/physical_button.c"
#include "data/physical_stick.c"
zoxel_declare_tag(Device)
zoxel_byte_component(MouseLock)
// 0 Disconnected, 1 KeyboardMouse, 2 Gamepad, 3 Touch, 4 Shared ???
zoxel_byte_component(DeviceMode)
zoxel_memory_component(DeviceLinks, ecs_entity_t)
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
zoxel_define_component(MouseLock)
zoxel_define_component(DeviceMode)
zoxel_define_memory_component(DeviceLinks)
zoxel_define_component(Keyboard)
zoxel_define_component(Mouse)
zoxel_define_component(Gamepad)
zoxel_define_component(Touchscreen)
spawn_prefab_keyboard(world);
spawn_prefab_mouse(world);
spawn_prefab_gamepad(world);
zoxel_system(MouseRaycasterSystem, EcsOnUpdate, [in] Mouse, [out] Raycaster)
zoxel_system(DraggerEndSystem, EcsOnLoad, [out] DragableState, [out] DraggerLink, [out] DraggingDelta)
zoxel_end_module(Inputs)

// todo: spawn/destroy device entity upon connection/removal
// todo: Add extract systems as systems

#endif
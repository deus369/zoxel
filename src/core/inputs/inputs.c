#ifndef zoxel_inputs
#define zoxel_inputs

#define zox_device_mode_none 0
#define zox_device_mode_keyboardmouse 1
#define zox_device_mode_gamepad 2
#define zox_device_mode_touchscreen 3
// #define zox_device_mode_shared 4 // mix between controller and idk?

#include "data/physical_button.c"
#include "data/physical_stick.c"
#include "data/finger.c"
zox_declare_tag(Device)
zoxel_byte_component(MouseLock)
zoxel_byte_component(DeviceMode)
zox_memory_component(DeviceLinks, ecs_entity_t)
#include "components/keyboard.c"
#include "components/mouse.c"
#include "components/gamepad.c"
#include "components/touchscreen.c"
#include "prefabs/mouse.c"
#include "prefabs/keyboard.c"
#include "prefabs/gamepad.c"
#include "prefabs/touchscreen.c"
#include "systems/mouse_raycaster_system.c"
#include "systems/dragger_end_system.c"
#include "systems/device_mode_system.c"
#include "util/keyboard_extract_util.c"
#include "util/mouse_extract_util.c"
#include "util/gamepad_util.c"
#include "util/touchscreen_extract_util.c"
#include "util/input_util.c"

zox_begin_module(Inputs)
zox_define_tag(Device)
zox_define_component(MouseLock)
zox_define_component(DeviceMode)
zox_define_memory_component(DeviceLinks)
zox_define_component(Keyboard)
zox_define_component(Mouse)
zox_define_component(Gamepad)
zox_define_component(Touchscreen)
spawn_prefab_keyboard(world);
spawn_prefab_mouse(world);
spawn_prefab_gamepad(world);
spawn_prefab_touchscreen(world);
zox_system_1(DeviceModeSystem, EcsOnLoad, [in] DeviceLinks, [out] DeviceMode)
zox_system(MouseRaycasterSystem, EcsPreUpdate, [in] DeviceLinks, [in] DeviceMode, [out] Raycaster)
zox_system(DraggerEndSystem, EcsOnLoad, [out] DragableState, [out] DraggerLink, [out] DraggingDelta)
zoxel_end_module(Inputs)

// todo: get change filters to work in multithreaded systems
// todo: spawn/destroy device entity upon connection/removal
// todo: Add extract systems as systems

#endif
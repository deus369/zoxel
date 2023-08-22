#ifndef zoxel_inputs
#define zoxel_inputs

// zoxel_settings
#define zox_device_mode_none 0
#define zox_device_mode_keyboardmouse 1
#define zox_device_mode_gamepad 2
#define zox_device_mode_touchscreen 3
#define zox_device_mode_max 4
const float joystick_min_cutoff = 0.01f;
const float joystick_cutoff_buffer = 0.14f;
// #define zox_device_mode_shared 4 // mix between controller and idk?
// zoxel_component_declares
#include "data/physical_button.c"
#include "data/physical_stick.c"
#include "data/finger.c"
zox_declare_tag(Device)
zox_byte_component(MouseLock)
zox_byte_component(DeviceMode)
zox_byte_component(DeviceModeDirty)
zox_memory_component(DeviceLinks, ecs_entity_t)
#include "components/keyboard.c"
#include "components/mouse.c"
#include "components/gamepad.c"
#include "components/touchscreen.c"
// zoxel_prefab_includes
#include "prefabs/mouse.c"
#include "prefabs/keyboard.c"
#include "prefabs/gamepad.c"
#include "prefabs/touchscreen.c"
// zoxel_system_declares
#include "systems/mouse_raycaster_system.c"
#include "systems/dragger_end_system.c"
#include "systems/device_mode_system.c"
#include "systems/device_mode_dirty_system.c"
// zoxel_util_includes
#include "util/keyboard_extract_util.c"
#include "util/mouse_extract_util.c"
#include "util/gamepad_util.c"
#include "util/touchscreen_extract_util.c"
#include "util/input_util.c"

void spawn_prefabs_inputs(ecs_world_t *world) {
    spawn_prefab_keyboard(world);
    spawn_prefab_mouse(world);
    spawn_prefab_gamepad(world);
    spawn_prefab_touchscreen(world);
}

zox_begin_module(Inputs)
// zoxel_component_defines
zox_define_tag(Device)
zox_define_component(MouseLock)
zox_define_component(DeviceMode)
zox_define_component(DeviceModeDirty)
zox_define_memory_component(DeviceLinks)
zox_define_component(Keyboard)
zox_define_component(Mouse)
zox_define_component(Gamepad)
zox_define_component(Touchscreen)
// zoxel_system_defines
zox_system(DeviceModeSystem, EcsOnLoad, [in] DeviceLinks, [in] DeviceMode, [out] DeviceModeDirty)
zox_system(MouseRaycasterSystem, EcsPreUpdate, [in] DeviceLinks, [in] DeviceMode, [out] Raycaster)
zox_system(DraggerEndSystem, EcsOnLoad, [out] DragableState, [out] DraggerLink, [out] DraggingDelta)
zox_system(DeviceModeDirtySystem, EcsPostUpdate, [out] DeviceMode, [out] DeviceModeDirty)
zoxel_end_module(Inputs)

// todo: get change filters to work in multithreaded systems
// todo: spawn/destroy device entity upon connection/removal
// todo: Add extract systems as systems

#endif
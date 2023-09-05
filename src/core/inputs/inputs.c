#ifndef zoxel_inputs
#define zoxel_inputs

// todo: get change filters to work in multithreaded systems
// todo: spawn/destroy device entity upon connection/removal
// todo: Add extract systems as systems

// zoxel_settings
#define zox_device_mode_none 0
#define zox_device_mode_keyboardmouse 1
#define zox_device_mode_gamepad 2
#define zox_device_mode_touchscreen 3
#define zox_device_mode_max 4
const float joystick_min_cutoff = 0.01f;
const float joystick_min_cutoff2 = 0.04f;
const float joystick_cutoff_buffer = 0.14f;
// const float joystick_cutoff_buffer2 = 0.01f;
// #define zox_device_mode_shared 4 // mix between controller and idk?
// zoxel_component_declares
#include "data/physical_button.c"
#include "data/physical_stick.c"
#include "data/finger.c"
zox_declare_tag(Device)
zox_declare_tag(Gamepad)
zox_declare_tag(Zevice)
zox_byte_component(DeviceButton)
zox_byte_component(ZeviceDisabled)
zox_component(DeviceStick, float2)
zox_byte_component(DeviceButtonType)
zox_byte_component(RealButtonIndex)
zox_byte_component(DeviceLayout)
zox_byte_component(MouseLock)
zox_byte_component(DeviceMode)
zox_byte_component(DeviceModeDirty)
zox_memory_component(DeviceButtonLinks, ecs_entity_t)
zox_memory_component(DeviceLinks, ecs_entity_t)
#include "components/keyboard.c"
#include "components/mouse.c"
#include "components/gamepad.c"
#include "components/touchscreen.c"
// zoxel_prefab_includes
#include "prefabs/device_button.c"
#include "prefabs/device_stick.c"
#include "prefabs/mouse.c"
#include "prefabs/keyboard.c"
#include "prefabs/gamepad.c"
#include "prefabs/touchscreen.c"
// zoxel_system_declares
#include "systems/zevice_button_enable_system.c"
#include "systems/mouse_raycaster_system.c"
#include "systems/dragger_end_system.c"
#include "systems/device_mode_system.c"
#include "systems/device_mode_dirty_system.c"
// zoxel_util_includes
#include "util/deadzone_util.c"
#include "util/input_util.c"

void spawn_prefabs_inputs(ecs_world_t *world) {
    spawn_prefab_device_button(world);
    spawn_prefab_device_stick(world);
    spawn_prefab_keyboard(world);
    spawn_prefab_mouse(world);
    spawn_prefab_gamepad(world);
    spawn_prefab_touchscreen(world);
}

zox_begin_module(Inputs)
// zoxel_component_defines
zox_define_tag(Device)
zox_define_tag(Gamepad)
zox_define_tag(Zevice)
zox_define_component(DeviceButton)
zox_define_component(DeviceStick)
zox_define_component(DeviceButtonType)
zox_define_component(RealButtonIndex)
zox_define_component(DeviceLayout)
zox_define_component(MouseLock)
zox_define_component(DeviceMode)
zox_define_component(DeviceModeDirty)
zox_define_memory_component(DeviceLinks)
zox_define_component(Keyboard)
zox_define_component(Mouse)
zox_define_component(Touchscreen)
zox_define_component(ZeviceDisabled)
// zoxel_system_defines
zox_system(DeviceModeSystem, EcsOnLoad, [in] DeviceLinks, [in] DeviceMode, [out] DeviceModeDirty)
zox_system(DraggerEndSystem, EcsOnLoad, [out] DragableState, [out] DraggerLink, [out] DraggingDelta)
zox_system(MouseRaycasterSystem, EcsPreUpdate, [in] DeviceLinks, [in] DeviceMode, [out] Raycaster)
zox_system(DeviceModeDirtySystem, EcsPostUpdate, [out] DeviceMode, [out] DeviceModeDirty)
zox_system(ZeviceButtonEnableSystem, EcsOnStore, [in] DeviceButton, [out] ZeviceDisabled)
zox_system(ZeviceStickEnableSystem, EcsOnStore, [in] DeviceStick, [out] ZeviceDisabled)
zoxel_end_module(Inputs)

#endif
#ifndef zoxel_inputs
#define zoxel_inputs

// todo: refactor keyboard and mouse to use zevices
// todo: reset zevice_stick and zevice_pointer in systems
// todo: extract touchscreen, keyboard, mouse in systems
// todo: sdl device disconnects, handle as spawning new entities, add to player if player mode is accepting new device (if they disconnect, put their control state in accepting)
// todo: get change filters to work in multithreaded systems
// todo: spawn/destroy device entity upon connection/removal
// todo: refactor deadzonoes into each individual zevice
// todo: hotkey system to do with bindings
// todo: hotkey ui

// zoxel_settings
#define zox_device_mode_none 0
#define zox_device_mode_keyboardmouse 1
#define zox_device_mode_gamepad 2
#define zox_device_mode_touchscreen 3
#define zox_device_mode_max 4
const float joystick_min_cutoff = 0.01f;
const float joystick_min_cutoff2 = 0.04f;
const float joystick_cutoff_buffer = 0.14f;
// zoxel_component_declares
#include "data/gamepad_flags.c"
#include "data/button_flags.c"
#include "data/physical_button.c"
#include "data/physical_stick.c"
#include "data/finger.c"
zox_declare_tag(Device)
zox_declare_tag(Zevice)
zox_declare_tag(Gamepad)
zox_declare_tag(Touchscreen)
zox_byte_component(ZeviceDisabled)
zox_byte_component(ZeviceButton)
zox_byte_component(ZevicePointer)
zox_component(ZeviceStick, float2)
zox_component(ZevicePointerPosition, int2)
zox_component(ZevicePointerDelta, int2)
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
// zoxel_prefab_includes
#include "prefabs/zevice_button.c"
#include "prefabs/zevice_stick.c"
#include "prefabs/zevice_pointer.c"
#include "prefabs/mouse.c"
#include "prefabs/keyboard.c"
#include "prefabs/gamepad.c"
#include "prefabs/touchscreen.c"
// zoxel_system_declares
#include "systems/zevice_button_reset_system.c"
#include "systems/zevice_button_enable_system.c"
#include "systems/mouse_raycaster_system.c"
#include "systems/dragger_end_system.c"
#include "systems/device_mode_system.c"
#include "systems/device_mode_dirty_system.c"
// zoxel_util_includes
#include "util/deadzone_util.c"

// move this to systems
void reset_input_devices(ecs_world_t *world) {
    device_reset_keyboard(world, keyboard_entity);
    device_reset_mouse(world, mouse_entity);
    device_reset_touchscreen(world, touchscreen_entity);
}

void spawn_prefabs_inputs(ecs_world_t *world) {
    spawn_prefab_device_button(world);
    spawn_prefab_device_stick(world);
    spawn_prefab_zevice_pointer(world);
    spawn_prefab_keyboard(world);
    spawn_prefab_mouse(world);
    spawn_prefab_gamepad(world);
    spawn_prefab_touchscreen(world);
    // test_device_button_flags();
}

zox_begin_module(Inputs)
// zoxel_component_defines
zox_define_tag(Device)
zox_define_tag(Zevice)
zox_define_tag(Gamepad)
zox_define_tag(Touchscreen)
zox_define_component(ZeviceButton)
zox_define_component(ZeviceStick)
zox_define_component(DeviceButtonType)
zox_define_component(RealButtonIndex)
zox_define_component(DeviceLayout)
zox_define_component(MouseLock)
zox_define_component(DeviceMode)
zox_define_component(DeviceModeDirty)
zox_define_memory_component(DeviceLinks)
zox_define_component(Keyboard)
zox_define_component(Mouse)
zox_define_component(ZeviceDisabled)
zox_define_component(ZevicePointer)
zox_define_component(ZevicePointerPosition)
zox_define_component(ZevicePointerDelta)
// zoxel_system_defines
zox_system(ZeviceButtonResetSystem, EcsOnLoad, [out] ZeviceButton)
zox_system(DeviceModeSystem, EcsPreUpdate, [in] DeviceLinks, [in] DeviceMode, [out] DeviceModeDirty)
zox_system(DraggerEndSystem, EcsPreUpdate, [out] DragableState, [out] DraggerLink, [out] DraggingDelta)
zox_system(MouseRaycasterSystem, EcsPreUpdate, [in] DeviceLinks, [in] DeviceMode, [out] Raycaster)
zox_system(DeviceModeDirtySystem, EcsPostUpdate, [out] DeviceMode, [out] DeviceModeDirty)
zox_system(ZeviceButtonEnableSystem, EcsOnStore, [in] ZeviceButton, [out] ZeviceDisabled)
zox_system(ZeviceStickEnableSystem, EcsOnStore, [in] ZeviceStick, [out] ZeviceDisabled)
zox_system(ZevicePointerEnableSystem, EcsOnStore, [in] ZevicePointer, [out] ZeviceDisabled)
zoxel_end_module(Inputs)

#endif
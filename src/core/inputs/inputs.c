#ifndef zoxel_inputs
#define zoxel_inputs

// zoxel_settings
#define zox_pipelines_devices_reset EcsOnLoad
#define zox_pipelines_devices_enables EcsOnStore
const float joystick_min_cutoff = 0.01f;
const float joystick_min_cutoff2 = 0.04f;
const float joystick_cutoff_buffer = 0.14f;
// zoxel_component_declares
#include "data/device_modes.c"
#include "data/gamepad_flags.c"
#include "data/button_flags.c"
#include "data/physical_button.c"
#include "data/physical_stick.c"
zox_declare_tag(Device)
zox_declare_tag(Zevice)
zox_declare_tag(Gamepad)
zox_declare_tag(Touchscreen)
zox_component_byte(ZeviceDisabled)
zox_component_byte(ZeviceButton)
zox_component_byte(ZevicePointer)
zox_component_byte(DeviceButtonType)
zox_component_byte(RealButtonIndex)
zox_component_byte(DeviceLayout)
zox_component_byte(MouseLock)
zox_component_byte(DeviceMode)
zox_component_byte(DeviceModeDirty)
zox_component_float2(ZeviceStick)
zox_component_int2(ZevicePointerPosition)
zox_component_int2(ZevicePointerDelta)
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
// zoxel_util_includes
#include "util/input_util.c"
#include "util/deadzone_util.c"
// zoxel_system_declares
#include "systems/zevice_button_reset_system.c"
#include "systems/zevice_pointer_reset_system.c"
#include "systems/zevice_pointer_delta_reset_system.c"
#include "systems/zevice_button_enable_system.c"
#include "systems/zevice_stick_enable_system.c"
#include "systems/zevice_pointer_enable_system.c"
#include "systems/mouse_raycaster_system.c"
#include "systems/dragger_end_system.c"
#include "systems/device_mode_system.c"
#include "systems/device_mode_dirty_system.c"

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
zox_define_component(Keyboard)
zox_define_component(Mouse)
zox_define_component_byte(ZeviceDisabled)
zox_define_component_byte(ZevicePointer)
zox_define_component_byte(ZeviceButton)
zox_define_component_byte(DeviceButtonType)
zox_define_component_byte(RealButtonIndex)
zox_define_component_byte(DeviceLayout)
zox_define_component_byte(MouseLock)
zox_define_component_byte(DeviceMode)
zox_define_component_byte(DeviceModeDirty)
zox_define_component_int2(ZevicePointerPosition)
zox_define_component_int2(ZevicePointerDelta)
zox_define_component_float2(ZeviceStick)
zox_define_memory_component(DeviceLinks)
// zoxel_system_defines
zox_system(ZeviceButtonResetSystem, zox_pipelines_devices_reset, [out] ZeviceButton)
zox_system(ZevicePointerResetSystem, zox_pipelines_devices_reset, [out] ZevicePointer)
zox_system(ZevicePointerDeltaResetSystem, zox_pipelines_devices_reset, [out] ZevicePointerDelta)  // has to be before other systems
zox_system(DeviceModeSystem, EcsPreUpdate, [in] DeviceLinks, [in] DeviceMode, [out] DeviceModeDirty)
zox_system(DraggerEndSystem, EcsPreUpdate, [out] DraggableState, [out] DraggerLink, [out] DraggingDelta)
zox_system(MouseRaycasterSystem, EcsPreUpdate, [in] DeviceLinks, [in] DeviceMode, [out] Raycaster)
zox_system(DeviceModeDirtySystem, zox_pipelines_devices_enables, [out] DeviceMode, [out] DeviceModeDirty)
zox_system(ZeviceButtonEnableSystem, zox_pipelines_devices_enables, [in] ZeviceButton, [out] ZeviceDisabled)
zox_system(ZeviceStickEnableSystem, zox_pipelines_devices_enables, [in] ZeviceStick, [out] ZeviceDisabled)
zox_system(ZevicePointerEnableSystem, zox_pipelines_devices_enables, [in] ZevicePointer, [out] ZeviceDisabled)
zoxel_end_module(Inputs)

#endif

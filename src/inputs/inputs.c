#ifndef zox_mod_inputs
#define zox_mod_inputs

#include "data/settings.c"
#include "data/device_modes.c"
#include "data/gamepad_flags.c"
#include "data/button_flags.c"
#include "data/physical_button.c"
#include "data/physical_stick.c"
zox_declare_tag(Device)
zox_declare_tag(Zevice)
zox_declare_tag(Gamepad)
zox_declare_tag(Touchscreen)
zox_declare_tag(Mouse)
zox_declare_tag(Finger)
zox_component_byte(ZeviceDisabled)
zox_component_byte(ZeviceButton)
zox_component_byte(ZevicePointer)
zox_component_byte(ZevicePointerRight)
zox_component_byte(DeviceButtonType)
zox_component_byte(RealButtonIndex)
zox_component_byte(DeviceLayout)
zox_component_byte(MouseLock)
zox_component_byte(DeviceMode)
zox_component_byte(DeviceModeDirty)
zox_component_float2(ZeviceStick)
zox_component_int2(ZevicePointerPosition)
zox_component_int2(ZevicePointerDelta)
zox_component_int2(ZeviceWheel)
zox_component_entity(DeviceLink)
zox_component_entity(MouseLink)
zox_component_entity(ZeviceLink)
zox_component_entity(VirtualZeviceLink)
zox_memory_component(DeviceButtonLinks, ecs_entity_t)
zox_memory_component(DeviceLinks, ecs_entity_t)
#include "components/keyboard.c"
#include "util/click_state.c"
#include "util/input_util.c"
#include "util/deadzone_util.c"
#include "prefabs/prefabs.c"
#include "systems/zevice_button_reset_system.c"
#include "systems/zevice_pointer_reset_system.c"
#include "systems/zevice_pointer_delta_reset_system.c"
#include "systems/zevice_button_enable_system.c"
#include "systems/zevice_stick_enable_system.c"
#include "systems/zevice_pointer_enable_system.c"
#include "systems/device_mode_system.c"
#include "systems/device_mode_dirty_system.c"

zox_begin_module(Inputs)
zox_define_tag(Device)
zox_define_tag(Zevice)
zox_define_tag(Gamepad)
zox_define_tag(Touchscreen)
zox_define_tag(Finger)
zox_define_tag(Mouse)
zox_define_component(Keyboard)
zox_define_component_byte(ZeviceDisabled)
zox_define_component_byte(ZevicePointer)
zox_define_component_byte(ZevicePointerRight)
zox_define_component_byte(ZeviceButton)
zox_define_component_byte(DeviceButtonType)
zox_define_component_byte(RealButtonIndex)
zox_define_component_byte(DeviceLayout)
zox_define_component_byte(MouseLock)
zox_define_component_byte(DeviceMode)
zox_define_component_byte(DeviceModeDirty)
zox_define_component_int2(ZevicePointerPosition)
zox_define_component_int2(ZevicePointerDelta)
zox_define_component_int2(ZeviceWheel)
zox_define_component_float2(ZeviceStick)
zox_define_component_entity(DeviceLink)
zox_define_component_entity(MouseLink)
zox_define_component_entity(ZeviceLink)
zox_define_component_entity(VirtualZeviceLink)
zox_define_memory_component(DeviceLinks)
zox_system(ZeviceButtonResetSystem, zox_pipelines_devices_reset, [out] ZeviceButton)
zox_system(ZevicePointerResetSystem, zox_pipelines_devices_reset, [out] ZevicePointer)
zox_system(ZevicePointerRightResetSystem, zox_pipelines_devices_reset, [out] ZevicePointerRight)
zox_system(ZevicePointerDeltaResetSystem, zox_pipelines_devices_reset, [out] ZevicePointerDelta) // remember: ZevicePointerDeltaResetSystem has to be before other systems
zox_system(DeviceModeSystem, zox_pip_raycasting, [in] DeviceLinks, [in] DeviceMode, [out] DeviceModeDirty)
zox_system(DeviceModeDirtySystem, zox_pipelines_devices_enables, [out] DeviceMode, [out] DeviceModeDirty)
zox_system(ZeviceButtonEnableSystem, zox_pipelines_devices_enables, [in] ZeviceButton, [out] ZeviceDisabled)
zox_system(ZeviceStickEnableSystem, zox_pipelines_devices_enables, [in] ZeviceStick, [out] ZeviceDisabled)
zox_system(ZevicePointerEnableSystem, zox_pipelines_devices_enables, [in] ZevicePointer, [out] ZeviceDisabled)
spawn_prefabs_inputs(world);
zoxel_end_module(Inputs)

#endif

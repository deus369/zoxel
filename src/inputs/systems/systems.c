#include "zevice_button_reset_system.c"
#include "zevice_pointer_reset_system.c"
#include "zevice_pointer_delta_reset_system.c"
#include "zevice_button_enable_system.c"
#include "zevice_stick_enable_system.c"
#include "zevice_pointer_enable_system.c"
#include "device_mode_system.c"
#include "device_mode_dirty_system.c"
#include "keyboard_reset_system.c"

void define_systems_input(ecs_world_t* world) {
    // resets
    zox_system(ZeviceButtonResetSystem, zox_pipelines_devices_reset, [out] ZeviceButton)
    zox_system(ZevicePointerResetSystem, zox_pipelines_devices_reset, [out] ZevicePointer)
    zox_system(ZevicePointerRightResetSystem, zox_pipelines_devices_reset, [out] ZevicePointerRight)
    zox_system(ZevicePointerDeltaResetSystem, zox_pipelines_devices_reset, [out] ZevicePointerDelta) // remember: ZevicePointerDeltaResetSystem has to be before other systems
    zox_system(KeyboardResetSystem, EcsOnStore, [out] Keyboard)
    // state changes
    zox_system(DeviceModeSystem, zox_pip_raycasting, [in] DeviceLinks, [in] DeviceMode, [out] DeviceModeDirty)
    zox_system(DeviceModeDirtySystem, zox_pipelines_devices_enables, [out] DeviceMode, [out] DeviceModeDirty)
    zox_system(ZeviceButtonEnableSystem, zox_pipelines_devices_enables, [in] ZeviceButton, [out] ZeviceDisabled)
    zox_system(ZeviceStickEnableSystem, zox_pipelines_devices_enables, [in] ZeviceStick, [out] ZeviceDisabled)
    zox_system(ZevicePointerEnableSystem, zox_pipelines_devices_enables, [in] ZevicePointer, [out] ZeviceDisabled)
}
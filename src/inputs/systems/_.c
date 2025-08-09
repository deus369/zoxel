#include "zevice_button_reset.c"
#include "zevice_pointer_reset.c"
#include "zevice_pointer_delta_reset_system.c"
#include "zevice_button_enable_system.c"
#include "zevice_stick_enable_system.c"
#include "zevice_pointer_enable_system.c"
#include "device_mode_dirty_system.c"
#include "keyboard_reset_system.c"
#include "zevice_pointer_right_reset_button.c"
#include "zevice_finger_reset_button.c"
#include "device_mode_system.c"

void define_systems_input(ecs* world) {
    // resets
    zox_system(ZevicePointerResetSystem, zoxp_inputs_reset,
            [out] ZevicePointer,
            [out] ZevicePointerOld)
    zox_system(ZeviceButtonResetSystem, zoxp_inputs_reset,
            [out] ZeviceButton)
    zox_system(ZeviceFingerResetSystem, zoxp_inputs_reset,
            [in] ZevicePointerOld,
            [out] ZevicePointerPosition,
            [out] ZevicePointerDelta,
            [none] Finger)
    zox_system(ZevicePointerRightResetSystem, zoxp_inputs_reset,
            [out] ZevicePointerRight)
    zox_system(ZevicePointerDeltaResetSystem, zoxp_inputs_reset,
            [out] ZevicePointerDelta)
    zox_system(KeyboardResetSystem, EcsOnStore,
            [out] Keyboard)
    // state changes
    zox_system(DeviceModeSystem, zoxp_inputs_update,
            [in] DeviceLinks,
            [in] DeviceMode,
            [out] DeviceModeDirty)
    zox_system(DeviceModeDirtySystem, zoxp_inputs_enable,
            [out] DeviceMode,
            [out] DeviceModeDirty)
    zox_system(ZeviceButtonEnableSystem, zoxp_inputs_enable,
            [in] ZeviceButton,
            [out] ZeviceDisabled)
    zox_system(ZeviceStickEnableSystem, zoxp_inputs_enable,
            [in] ZeviceStick,
            [out] ZeviceDisabled)
    zox_system(ZevicePointerEnableSystem, zoxp_inputs_enable,
            [in] ZevicePointer,
            [out] ZeviceDisabled)
}
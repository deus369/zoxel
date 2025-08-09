#include "joysticks.c"

void define_systems_touch(ecs *world) {
    zox_system_1(VirtualJoystickSystem, zoxp_transforms,
             [in] inputs.DeviceLink,
             [in] raycasts.RaycasterResult,
             [in] inputs.ZevicePointer,
             [in] inputs.VirtualZeviceLink,
             [none] inputs.Zevice);
}
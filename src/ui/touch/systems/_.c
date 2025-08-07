#include "joysticks.c"

// zox_pipelines_pre_render
void define_systems_touch(ecs *world) {
    zox_system_1(VirtualJoystickSystem, EcsPreStore,
             [in] inputs.DeviceLink,
             [in] raycasts.RaycasterResult,
             [in] inputs.ZevicePointer,
             [in] inputs.VirtualZeviceLink,
             [none] inputs.Zevice);
}
#include "gamepad_extract_system.c"
#include "touchscreen_extract_system.c"
#include "mouse_extract_system.c"
#include "mouse_constrain_system.c"

void define_systems_sdl_inputs(ecs_world_t* world) {
#ifdef zox_sdl
    zox_system_1(GamepadExtractSystem, zoxp_sdl,
        [in] hierarchys.Children,
        [in] SDLGamepad,
        [none] inputs.Gamepad)
#endif
    zox_system_1(TouchscreenExtractSystem, zoxp_sdl,
        [in] hierarchys.Children,
        [in] apps.AppLink,
        [out] generic.ScreenDimensions,
        [none] inputs.Touchscreen)
    zox_system_1(MouseExtractSystem, zoxp_sdl,
        [in] hierarchys.Children,
        [in] apps.AppLink,
        [none] inputs.Mouse)
    zox_system_1(MouseConstrainSystem, zoxp_sdl,
        [in] inputs.DeviceDisabled,
        [in] inputs.MouseLock,
        [in] hierarchys.Children,
        [in] apps.AppLink,
        [none] inputs.Mouse)
}
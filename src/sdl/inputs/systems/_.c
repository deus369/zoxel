#include "gamepad_extract_system.c"
#include "touchscreen_extract_system.c"
#include "mouse_extract_system.c"
#include "mouse_constrain_system.c"

void define_systems_sdl_inputs(ecs_world_t* world) {
#ifdef zox_lib_sdl
    zox_system_1(GamepadExtractSystem, zox_extract_pipeline,
        [in] hierarchys.Children,
        [in] SDLGamepad,
        [none] inputs.Gamepad)
#endif
    zox_system_1(TouchscreenExtractSystem, zox_extract_pipeline,
        [in] hierarchys.Children,
        [in] apps.AppLink,
        [out] generic.ScreenDimensions,
        [none] inputs.Touchscreen)
    zox_system_1(MouseExtractSystem, zox_extract_pipeline,
        [in] hierarchys.Children,
        [in] apps.AppLink,
        [none] inputs.Mouse)
    zox_system_1(MouseConstrainSystem, zox_extract_pipeline,
        [in] inputs.MouseLock,
        [in] hierarchys.Children,
        [in] apps.AppLink,
        [none] inputs.Mouse)
}
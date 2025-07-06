#ifndef zox_sdl_inputs
#define zox_sdl_inputs

#include "data/settings.c"
#include "data/sdl_gamepad.c"
#include "util/_.c"
#include "systems/_.c"

void initialize_apps_input(ecs_world_t *world) {
    initialize_sdl_input();
#ifdef zox_lib_sdl
    zox_prefab_add(prefab_gamepad, SDLGamepad)
#endif
}

zox_begin_module(SdlInputs)
#ifdef zox_lib_sdl
    zox_define_component_w_dest(SDLGamepad)
    zox_system_1(GamepadExtractSystem, zox_extract_pipeline, [in] Children, [in] SDLGamepad, [none] inputs.Gamepad)
#endif
    zox_system_1(TouchscreenExtractSystem, zox_extract_pipeline, [in] Children, [out] ScreenDimensions, [none] inputs.Touchscreen)
    zox_system_1(MouseExtractSystem, zox_extract_pipeline, [in] Children, [none] inputs.Mouse)
    zox_system_1(MouseConstrainSystem, zox_extract_pipeline, [in] MouseLock, [in] Children, [none] inputs.Mouse)
    initialize_apps_input(world);
zox_end_module(SdlInputs)

#endif

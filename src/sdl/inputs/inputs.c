#ifndef zox_sdl_inputs
#define zox_sdl_inputs

byte global_any_fingers_down = 0;
#include "components/sdl_gamepad.c"
#include "util/util.c"
#include "systems/gamepad_extract_system.c"
#include "systems/touchscreen_extract_system.c"
#include "systems/mouse_extract_system.c"
#include "systems/mouse_constrain_system.c"

void initialize_apps_input(ecs_world_t *world) {
    initialize_sdl_input();
    zox_prefab_add(prefab_gamepad, SDLGamepad)
}

zox_begin_module(SdlInputs)
    zox_define_component_w_dest(SDLGamepad)
    zox_system_1(GamepadExtractSystem, zox_extract_pipeline, [in] Children, [in] SDLGamepad, [none] inputs.Gamepad)
    zox_system_1(TouchscreenExtractSystem, zox_extract_pipeline, [in] Children, [out] ScreenDimensions, [none] inputs.Touchscreen)
    zox_system_1(MouseExtractSystem, zox_extract_pipeline, [in] Children, [none] inputs.Mouse)
    zox_system_1(MouseConstrainSystem, zox_extract_pipeline, [in] MouseLock, [in] Children, [none] inputs.Mouse)
    initialize_apps_input(world);
zox_end_module(SdlInputs)

#endif

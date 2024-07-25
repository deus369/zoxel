#ifndef zox_apps_inputs
#define zox_apps_inputs

#include "util/sdl_key_util.c"
#include "util/keyboard_extract_util.c"
#include "util/mouse_extract_util.c"
#include "util/touchscreen_extract_util.c"
#include "util/gamepad_extract_util.c"
#include "util/input_util.c"
#include "util/cursor.c"
#include "systems/gamepad_extract_system.c"
#include "systems/touchscreen_extract_system.c"
#include "systems/mouse_extract_system.c"
#include "systems/mouse_constrain_system.c"

void initialize_apps_input(ecs_world_t *world) {
    initialize_sdl_input();
}

zox_begin_module(AppsInputs)
zox_system_1(GamepadExtractSystem, zox_extract_pipeline, [in] Children, [none] inputs.Gamepad)
zox_system_1(TouchscreenExtractSystem, zox_extract_pipeline, [in] Children, [out] ScreenDimensions, [none] inputs.Touchscreen)
zox_system_1(MouseExtractSystem, zox_extract_pipeline, [in] Children, [none] inputs.Mouse)
zox_system_1(MouseConstrainSystem, zox_extract_pipeline, [in] MouseLock, [in] Children, [none] inputs.Mouse)
initialize_apps_input(world);
zoxel_end_module(AppsInputs)

#endif

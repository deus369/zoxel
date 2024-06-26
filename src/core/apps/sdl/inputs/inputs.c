#ifndef zox_apps_inputs
#define zox_apps_inputs

#define zox_extract_pipeline EcsOnLoad
#include "util/sdl_key_util.c"
#include "util/keyboard_extract_util.c"
#include "util/mouse_extract_util.c"
#include "util/touchscreen_extract_util.c"
#include "util/gamepad_extract_util.c"
#include "util/input_util.c"
#include "util/cursor.c"
#include "systems/gamepad_extract_system.c"
#include "systems/touchscreen_extract_system.c"
#include "systems/mouse_constrain_system.c"

void initialize_apps_input(ecs_world_t *world) {
    initialize_sdl_input();
}

zox_begin_module(AppsInputs)
zox_system_1(TouchscreenExtractSystem, zox_extract_pipeline, [in] inputs.Touchscreen, [in] Children)
zox_system_1(GamepadExtractSystem, zox_extract_pipeline, [in] Children, [none] inputs.Gamepad)
zox_system_1(MouseConstrainSystem, zox_pip_mainthread, [in] MouseLock)
initialize_apps_input(world);
zoxel_end_module(AppsInputs)

#endif

#ifndef zoxel_apps_inputs
#define zoxel_apps_inputs

// useful
#define zox_extract_pipeline EcsOnLoad // EcsOnLoad | EcsPostLoad
#include "util/sdl_key_util.c"
#include "util/keyboard_extract_util.c"
#include "util/mouse_extract_util.c"
#include "util/touchscreen_extract_util.c"
#include "util/gamepad_extract_util.c"
#include "util/input_util.c"
#include "util/mouse_util.c"
// systems
#include "systems/gamepad_extract_system.c"
#include "systems/touchscreen_extract_system.c"
#include "systems/mouse_constrain_system.c"

void initialize_apps_input(ecs_world_t *world) {
    initialize_sdl_input();
}

zox_begin_module(AppsInputs)
// systems
zox_system(TouchscreenExtractSystem, zox_extract_pipeline, [in] inputs.Touchscreen, [in] Children)
zox_system(GamepadExtractSystem, zox_extract_pipeline, [in] inputs.Gamepad, [in] Children)
zox_system_1(MouseConstrainSystem, main_thread_pipeline, [in] MouseLock)
zoxel_end_module(AppsInputs)

#endif

#ifndef zox_sdl_inputs
#define zox_sdl_inputs

#include "data/settings.c"
#include "data/sdl_gamepad.c"
#include "util/_.c"
#include "systems/_.c"

void initialize_apps_input(ecs_world_t *world) {
    initialize_sdl_input();
#ifdef zox_sdl
    zox_prefab_add(prefab_gamepad, SDLGamepad)
#endif
}

zox_begin_module(SdlInputs)
#ifdef zox_sdl
    zox_define_component_w_dest(SDLGamepad)
#endif
    define_systems_sdl_inputs(world);
    initialize_apps_input(world);
zox_end_module(SdlInputs)

#endif
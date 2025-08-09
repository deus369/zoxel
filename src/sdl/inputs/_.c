#ifndef zox_sdl_inputs
#define zox_sdl_inputs

#include "data/settings.c"
#include "data/sdl_gamepad.c"
#include "util/_.c"
#include "systems/_.c"

void spawn_prefabs_sdl_input(ecs* world) {
#ifdef zox_sdl
    zox_prefab_add(prefab_gamepad, SDLGamepad);
#endif
}

zox_begin_module(SdlInputs)
#ifdef zox_sdl
    zox_define_component_w_dest(SDLGamepad);
#endif
    define_systems_sdl_inputs(world);
    initialize_sdl_input();
    add_hook_spawn_prefabs(spawn_prefabs_sdl_input);
zox_end_module(SdlInputs)

#endif
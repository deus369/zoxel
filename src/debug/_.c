#if !defined(zoxm_debug) && defined(zoxm_players)
#define zoxm_debug

#include "data/settings.c"
#include "util/amd.c"
#include "util/system.c"
#include "systems/game_debug_label_system.c"

void dispose_debug(ecs_world_t* world, void* ctx) {
    (void) world;
    (void) ctx;
    dispose_amd();
}

zox_begin_module(Debug)
    // zox_system(GameDebugLabelSystem, EcsOnStore, [out] texts.ZextDirty, [out] texts.TextData, [none] game.u.i.GameDebugLabel)
    initialize_amd();
    zox_module_dispose(dispose_debug)
zox_end_module(Debug)

#endif

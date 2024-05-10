#ifndef zox_actions_ui
#define zox_actions_ui

zox_declare_user_data(Actionbar)
#include "prefabs/actionbar.c"

void spawn_prefabs_actions_ui(ecs_world_t *world) {
    // spawn_prefab_actionbar(world);
}

zox_begin_module(ActionsUI)
zox_define_user_data(Actionbar)
// spawn_prefab_skill(world);
zoxel_end_module(Actions)

#endif

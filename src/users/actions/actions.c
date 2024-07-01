#ifndef zox_mod_actions
#define zox_mod_actions

zox_declare_user_data(Action)
#include "prefabs/action.c"
#include "util/character_actions.c"
#include "ui/ui.c"

void spawn_prefabs_actions(ecs_world_t *world) {
    spawn_prefab_action(world);
    spawn_prefabs_actions_ui(world);
    zox_prefab_add(prefab_character3D, ActionLinks)
}

zox_begin_module(Actions)
zox_define_user_data(Action)
zox_import_module(ActionsUI)
spawn_prefabs_actions(world);
zoxel_end_module(Actions)

#endif

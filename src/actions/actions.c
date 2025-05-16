#if !defined(zox_mod_actions) && defined(zox_mod_users)
#define zox_mod_actions

zox_declare_user_data(Action)
#include "prefabs/action.c"
#include "util/character_actions.c"
#include "ui/ui.c"

void set_linked_action(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e) {
    if (!zox_has(user, ActionLinks)) return;
    zox_get_muter(user, ActionLinks, datas)
    if (index >= datas->length) return;
    datas->value[index] = e;
}

void spawn_prefabs_actions(ecs_world_t *world) {
    spawn_prefab_action(world);
    spawn_prefabs_actions_ui(world);
    zox_prefab_add(prefab_character3D, ActionLinks)
}

zox_begin_module(Actions)
    zox_define_user_data(Action)
    zox_import_module(ActionsUI)
    spawn_prefabs_actions(world);
    add_hook_spawned_character3D(&spawn_character_actions);
zox_end_module(Actions)

#endif

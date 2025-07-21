#include "action.c"

void set_linked_action(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e) {
    if (!zox_has(user, ActionLinks)) {
        return;
    }
    zox_get_muter(user, ActionLinks, datas)
    if (index >= datas->length) {
        return;
    }
    datas->value[index] = e;
}

void spawn_prefabs_actions(ecs_world_t *world) {
    spawn_prefab_action(world);
    if (zox_valid(prefab_character3)) {
        zox_prefab_add(prefab_character3, ActionLinks)
    }
}
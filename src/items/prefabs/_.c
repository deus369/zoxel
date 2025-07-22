#include "user_item.c"

void spawn_prefabs_items(ecs_world_t *world) {
    prefab_item = spawn_prefab_item(world);
    zox_set(prefab_item, Quantity, { 1 })
    zox_prefab_character_add(ItemLinks)
    if (prefab_realm) {
        zox_prefab_add(prefab_realm, ItemLinks)
    }
}
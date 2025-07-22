#include "state.c"
#include "level.c"
#include "regen.c"
#include "attribute.c"
#include "stat.c"

void spawn_prefabs_stats(ecs_world_t *world) {
    spawn_prefab_stat(world);
    // zox_prefab_add(prefab_realm, StatLinks)
    if (prefab_realm) {
        zox_prefab_set(prefab_realm, StatLinks, { 0, NULL })
    }
    if (prefab_character3) {
        zox_prefab_character_set(StatLinks, { 0, NULL })
        zox_prefab_character_set(DotLinks, { 0, NULL })
    }
}
#include "stats.c"
#include "stat.c"
ecs_entity_t meta_stat_soul;
ecs_entity_t meta_stat_health;

void spawn_prefabs_stats(ecs_world_t *world) {
    spawn_prefab_stat(world);
    zox_prefab_add(prefab_character3D, StatLinks)
    zox_prefab_add(prefab_character3D, DotLinks)
}

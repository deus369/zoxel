#include "stats.c"
#include "stat.c"
ecs_entity_t meta_stat_soul;
ecs_entity_t meta_stat_health;
ecs_entity_t meta_stat_energy;
ecs_entity_t meta_stat_mana;
ecs_entity_t meta_stat_regen_health;
ecs_entity_t meta_stat_regen_energy;
ecs_entity_t meta_stat_regen_mana;
ecs_entity_t meta_stat_strength;

void spawn_prefabs_stats(ecs_world_t *world) {
    // zox_prefab_add(prefab_realm, StatLinks)
    zox_prefab_set(prefab_realm, StatLinks, { 0, NULL })
    zox_prefab_set(prefab_character3D, StatLinks, { 0, NULL })
    zox_prefab_set(prefab_character3D, DotLinks, { 0, NULL })
    spawn_prefab_stat(world);
}

#if !defined(zox_mod_combat) && defined(zox_mod_users)
#define zox_mod_combat

zox_component_byte(Dead)
zox_component_double(DiedTime)
zox_component_entity(LastDamager)
#include "systems/death_clean_system.c"
zox_increment_system(Dead, zox_dirty_end)

void spawn_prefabs_combat(ecs_world_t *world) {
    // stats / death
    zox_prefab_character_set(Dead, { 0 })
    zox_prefab_character_set(DiedTime, { 0 })
    zox_prefab_character_set(LastDamager, { 0 })
}

zox_begin_module(Combat)
    zox_define_component_byte(Dead)
    zox_define_component_double(DiedTime)
    zox_define_component_entity(LastDamager)
    zox_define_increment_system(Dead, EcsOnLoad)
    zox_system(DeathCleanSystem, EcsOnUpdate,
        [in] combat.Dead,
        [in] DiedTime)
    spawn_prefabs_combat(world);
zox_end_module(Combat)

#endif

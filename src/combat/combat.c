#if !defined(zox_mod_combat) && defined(zox_mod_users)
#define zox_mod_combat

zox_component_byte(Dead)
zox_component_double(DiedTime)
zox_component_entity(LastDamager)
#include "systems/death_clean_system.c"

void spawn_prefabs_combat(ecs_world_t *world) {
    // stats / death
    zox_prefab_set(prefab_character3D, Dead, { 0 })
    zox_prefab_set(prefab_character3D, DiedTime, { 0 })
    zox_prefab_set(prefab_character3D, LastDamager, { 0 })
}

zox_begin_module(Combat)
    zox_define_component_byte(Dead)
    zox_define_component_double(DiedTime)
    zox_define_component_entity(LastDamager)
    zox_system(DeathCleanSystem, EcsOnUpdate, [in] Dead, [in] DiedTime)
    spawn_prefabs_combat(world);
zoxel_end_module(Combat)

#endif

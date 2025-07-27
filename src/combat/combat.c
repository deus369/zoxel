#if !defined(zox_mod_combat) && defined(zox_mod_users)
#define zox_mod_combat

zox_component_byte(CombatState)
zox_component_entity(LastDamager)
zox_component_double(LastCombatTime)
zox_component_byte(Dead)
zox_component_double(DiedTime)
#include "states/_.c"
#include "systems/_.c"
#include "util/_.c"

zox_begin_module(Combat)
    zox_define_component_byte(Dead)
    zox_define_component_double(DiedTime)
    zox_define_component_double(LastCombatTime)
    zox_define_component_entity(CombatState)
    zox_define_component_entity(LastDamager)
    define_systems_combat(world);
    spawn_prefabs_combat(world);
zox_end_module(Combat)

#endif

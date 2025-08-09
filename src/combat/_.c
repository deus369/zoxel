#if !defined(zoxm_combat) && defined(zoxm_users)
#define zoxm_combat

zoxc_byte(CombatState);
zoxc_entity(LastDamager);
zoxc_double(LastCombatTime);
zoxc_byte(Dead);
zoxc_double(DiedTime);
#include "states/_.c"
#include "prefabs/_.c"
#include "systems/_.c"
#include "util/_.c"

zox_begin_module(Combat)
    zox_define_component_byte(Dead);
    zox_define_component_double(DiedTime);
    zox_define_component_double(LastCombatTime);
    zox_define_component_entity(CombatState);
    zox_define_component_entity(LastDamager);
    define_systems_combat(world);
    add_hook_spawn_prefabs(spawn_prefabs_combat);
zox_end_module(Combat)

#endif

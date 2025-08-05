void spawn_prefabs_combat(ecs_world_t *world) {
    // stats / death
    if (prefab_character3) {
        zox_prefab_character_set(Dead, { 0 });
        zox_prefab_character_set(DiedTime, { 0 });
        zox_prefab_character_set(LastDamager, { 0 });
        zox_prefab_character_set(LastCombatTime, { 0 });
        zox_prefab_character_set(CombatState, { zox_combat_peace });
    }
}

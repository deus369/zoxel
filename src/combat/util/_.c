void spawn_prefabs_combat(ecs_world_t *world) {
    // stats / death
    zox_prefab_character_set(Dead, { 0 })
    zox_prefab_character_set(DiedTime, { 0 })
    zox_prefab_character_set(InCombat, { 0 })
    zox_prefab_character_set(LastDamager, { 0 })
    zox_prefab_character_set(LastCombatTime, { 0 })
}

// zox_current_time
void combat_on_hit(ecs_world_t* world, ecs_entity_t e, ecs_entity_t e2) {
    if (!zox_valid(e)) {
        return;
    }
    zox_set(e, LastDamager, { e2 })
    zox_geter_value(e, InCombat, byte, combat_state)
    if (!(combat_state == zox_combat_battle || combat_state == zox_combat_enter_battle)) {
        zox_set(e, InCombat, { zox_combat_trigger_battle })
    }
    // any exchanges we update their timer
    zox_set(e, LastCombatTime, { zox_current_time })
    zox_set(e2, LastCombatTime, { zox_current_time })
}
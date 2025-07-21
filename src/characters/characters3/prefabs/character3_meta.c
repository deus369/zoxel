ecs_entity_t spawn_prefab_character3_meta(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("character3_meta")
    zox_prefab_set(e, ModelLink, { 0 })
    zox_prefab_set(e, SpawnChance, { 0 })
    return e;
}
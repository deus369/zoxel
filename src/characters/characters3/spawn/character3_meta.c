ecs_entity_t spawn_character3_meta(ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t vox,
    const byte chance)
{
    zox_instance(prefab)
    zox_name("character3_meta")
    zox_set(e, ModelLink, { vox })
    zox_set(e, SpawnChance, { chance })
    return e;
}
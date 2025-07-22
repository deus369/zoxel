// we link our instances to model links
//      - set ModelLink->value per lod change -  RenderLodDirty

ecs_entity_t spawn_prefab_character3_instanced(ecs_world_t *world, const ecs_entity_t prefab) {
    const ecs_entity_t e = spawn_prefab_character3(world, prefab);
    zox_make_prefab(e)
    // zox_prefab_child(prefab)
    zox_prefab_name("character3_instanced")
    // generation
    zox_prefab_set(e, Rotation3D, { quaternion_identity })
    // zox_prefab_set(e, Rotation3D, { quaternion_identity })
    zox_prefab_set(e, RenderDisabled, { 0 })
    return e;
}
// we link our instances to model links
//      - set ModelLink->value per lod change -  RenderLodDirty

ecs_entity_t spawn_prefab_character3_instanced(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("character3_instanced")
    zox_add_tag(e, Character3D)
    // generation

}
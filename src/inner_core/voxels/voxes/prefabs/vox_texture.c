ecs_entity_t spawn_prefab_vox_texture(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_vox_texture")
    zox_add_tag(e, VoxTexture)
    zox_prefab_add(e, VoxLink)
    zox_prefab_add(e, VoxBakeSide)
    zox_prefab_set(e, GenerateTexture, { zox_generate_texture_trigger })
    return e;
}

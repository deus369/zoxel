// a block that is for a block vox
ecs_entity_t spawn_prefab_block_vox_meta(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t prefab_block_vox) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_block_vox_meta")
    zox_prefab_add(e, ModelLink)
    // zox_prefab_set(e, BlockModel, { zox_block_vox })
    return e;
}

ecs_entity_t spawn_block_vox_meta(ecs_world_t *world, const SpawnBlock *data) {
    zox_instance(data->prefab)
    zox_name(data->name) // "block_vox_meta")
    if (data->prefab_block_vox) {
        zox_prefab_set(e, BlockPrefabLink, { data->prefab_block_vox })
    }
    zox_set(e, BlockIndex, { data->index })
    zox_set(e, Color, { data->color })
    if (data->model) zox_set(e, BlockModel, { data->model })
    if (data->tag) zox_add_tag_id(e, data->tag)
    if (data->disable_collision) zox_set(e, BlockCollider, { zox_block_air })
    if (data->vox_offset) zox_set(e, BlockVoxOffset, { 1 })
    if (data->vox) zox_set(e, ModelLink, { data->vox }) //  && !data->bake_vox
    if (data->bake_vox) {
        // Textures *textures = zox_get_mut(e, Textures)
        Textures *textures = &((Textures) { 0, NULL });
        resize_memory_component(Textures, textures, ecs_entity_t, 6)
        for (int i = 0; i < 6; i++) {
            const ecs_entity_t e2 = spawn_texture(world, data->prefab_texture, voxel_texture_size);
            zox_set(e2, VoxLink, { data->vox })
            zox_set(e2, VoxBakeSide, { i })
            textures->value[i] = e2;
        }
        // zox_modified(e, Textures)
        zox_set(e, Textures, { textures->length, textures->value })
    }
    // zox_log(" + generated block [vox] name [%s]\n", name)
    zox_set(e, ZoxName, { text_to_zext(data->name) })
    return e;
}

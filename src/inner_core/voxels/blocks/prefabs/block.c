ecs_entity_t spawn_prefab_block(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_block")
    zox_add_tag(e, Voxel)
    zox_prefab_set(e, Color, { color_white })
    zox_prefab_set(e, BlockModel, { zox_block_solid })
    zox_prefab_set(e, BlockCollider, { zox_block_solid })
    zox_prefab_set(e, Textures, { 0, NULL })
    return e;
}

ecs_entity_t spawn_block(ecs_world_t *world, const SpawnBlock *data) {
    zox_instance(data->prefab)
    zox_name("voxel")
    zox_set(e, Color, { data->color })
    if (data->model != zox_block_air) zox_set(e, BlockModel, { data->model })
    if (data->tag) zox_add_tag_id(e, data->tag);
    if (data->vox) zox_set(e, ModelLink, { data->vox })
    if (data->disable_collision) zox_set(e, BlockCollider, { zox_block_air })
    if (data->vox_offset) zox_set(e, BlockVoxOffset, { 1 })
    const unsigned char textures_count = data->textures;
    Textures *textures = zox_get_mut(e, Textures)
    resize_memory_component(Textures, textures, ecs_entity_t, textures_count)
    for (int i = 0; i < textures_count; i++) {
        ecs_entity_t e2;
        if (data->vox_texture) {
            e2 = spawn_texture(world, prefab_texture, voxel_texture_size);
            zox_add_tag(e2, VoxTexture)
            zox_set(e2, VoxLink, { data->vox_texture })
            zox_set(e2, GenerateTexture, { 1 })
            zox_set(e2, VoxBakeSide, { i })
            // zox_set(e2, Color, { data->color })
        } else {
            // todo: base grass off dirt, as well as sand, using HSV color contrasts
            e2 = spawn_texture_dirt(world, prefab_texture_noise, data->seed + i, data->color);
            if (data->texture_tag) zox_add_tag_id(e2, data->texture_tag);
        }
        textures->value[i] = e2;
    }
    zox_modified(e, Textures)
    return e;
}


/*ecs_entity_t spawn_block_multi_texture(ecs_world_t *world, const SpawnBlock *data) {
    zox_instance(data->prefab)
    zox_name("voxel")
    if (data->model != zox_block_air) zox_set(e, BlockModel, { data->model })
    if (data->tag) zox_add_tag_id(e, data->tag);
    Textures *textures = zox_get_mut(e, Textures)
    unsigned char textures_count = 6;
    resize_memory_component(Textures, textures, ecs_entity_t, textures_count)
    for (int i = 0; i < textures_count; i++) {
        // todo: base grass off dirt, as well as sand, using HSV color contrasts
        const ecs_entity_t e2 = spawn_texture_dirt(world, prefab_texture_noise, data->seed + i, data->color);
        if (data->texture_tag && i != 3) zox_add_tag_id(e2, data->texture_tag);
        textures->value[i] = e2;
    }
    zox_modified(e, Textures)
    return e;
}
*/

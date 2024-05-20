ecs_entity_t spawn_prefab_voxel(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_voxel")
    zox_add_tag(e, Voxel)
    zox_prefab_set(e, BlockModel, { zox_block_solid })
    zox_prefab_set(e, BlockCollider, { zox_block_solid })
    zox_prefab_set(e, Textures, { 0, NULL })
    return e;
}

ecs_entity_t spawn_voxel(ecs_world_t *world, const SpawnVoxel *data) {
    zox_instance(data->prefab)
    zox_name("voxel")
    if (data->model != zox_block_air) zox_set(e, BlockModel, { data->model })
    if (data->tag) zox_add_tag_id(e, data->tag);
    Textures *textures = zox_get_mut(e, Textures)
    resize_memory_component(Textures, textures, ecs_entity_t, 1)
    for (int i = 0; i < 1; i++) {
        // todo: base grass off dirt, as well as sand, using HSV color contrasts
        const ecs_entity_t e2 = spawn_texture_dirt(world, prefab_texture_noise, data->seed + i, data->color);
        if (data->texture_tag) zox_add_tag_id(e2, data->texture_tag);
        textures->value[i] = e2;
    }
    zox_modified(e, Textures)
    return e;
}

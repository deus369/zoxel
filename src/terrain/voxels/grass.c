ecs_entity_t spawn_realm_block_grass(ecs_world_t *world, const byte index, const color block_color) {
    const ecs_entity_t vox = spawn_vox_basic(world, prefab_vox);
    zox_set(vox, Color, { block_color })
    zox_add_tag(vox, VoxRubble)
    zox_set(vox, GenerateVox, { 1 })
    zox_set(vox, RenderLod, { 0 })
    zox_set_unique_name(vox, "realm_block_grass")
    zox_set(vox, RubbleHeight, { 24 })
    zox_set(vox, RubbleCount, { 8000 })
    if (!vox) {
        zox_log(" ! grass_vox model not found.\n")
    }
    // use instanced mesh prefab
    SpawnBlock data = {
        .index = (byte) (index + 1),
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        .name = "grass",
        .color = generate_random_voxel_color(),
        .tag = zox_id(BlockVox),
        .model = zox_block_vox,
        .disable_collision = 1,
        .prefab_texture = prefab_vox_texture,
        .vox = vox
    };
    // for instancing
    zox_prefab_child_named(prefab_block_vox_instanced, prefab_block_vox2)
    data.prefab_block_vox = prefab_block_vox2;
    zox_set(prefab_block_vox2, InstanceLink, { vox })
    if (disable_block_voxes) {
        data.bake_vox = 1;
        data.vox = spawn_vox_generated_invisible(world, prefab_vox_generated, block_color);
        data.model = 0;
        data.tag = 0;
    }
    const ecs_entity_t e = spawn_block_vox_meta(world, &data);
    return e;
}
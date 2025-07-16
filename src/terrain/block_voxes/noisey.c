ecs_entity_t spawn_realm_block_noisey(ecs_world_t *world, const byte index, char* name, const color block_color) {
    // vox
    const ecs_entity_t vox = spawn_vox_generated_invisible(world, prefab_vox_generated, block_color);
    zox_set_unique_name(vox, "dirt_pile")
    zox_set(vox, VoxType, { vox_type_noisey })
    // block
    SpawnBlock data = {
        .prefab = prefab_block_vox_meta,
        .prefab_block_vox = prefab_block_vox,
        .vox = vox,
        .tag = zox_id(BlockVox),
        .model = zox_block_vox,
        .index = index,
        .seed = generate_voxel_seed(index),
        .name = name,
        .color = block_color,
    };
    process_disabled_block_vox(world, &data, 1);
    return spawn_block_vox_meta(world, &data);
}

// spawn_data.name = generate_name();

// this is a more detailed version of dirt! non baked
// remember: to add air back onto sides
// make disables more systematic
/*if (disable_block_voxes) {
    spawn_data.bake_vox = 1;
    const ecs_entity_t vox_disabled = spawn_vox_generated_invisible(world, prefab_vox_generated, (color) { 25, 5, 5, 255 });
    spawn_data.vox = vox_disabled;
    } else {
        spawn_data.prefab = prefab_block;
        e = spawn_block(world, &spawn_data);
*/
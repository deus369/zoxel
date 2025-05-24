

ecs_entity_t spawn_realm_block_noisey(ecs_world_t *world, const byte index, char* name, const color block_color) {
    SpawnBlock spawn_data = {
        // .prefab_block_vox = prefab_block_vox,
        .index = index,
        .seed = generate_voxel_seed(index + 1),
        .prefab_texture = prefab_vox_texture
    };
    spawn_data.name = name; // "dirt_vox";
    spawn_data.color = block_color;
    // this is a more detailed version of dirt! non baked
    // remember: to add air back onto sides
    if (disable_block_voxes) {
        spawn_data.bake_vox = 1;
        const ecs_entity_t vox_disabled = spawn_vox_generated_invisible(world, prefab_vox_generated, (color) { 25, 5, 5, 255 });
        spawn_data.vox = vox_disabled;
    } else {
        const ecs_entity_t vox = spawn_vox_generated_invisible(world, prefab_vox_generated, block_color);
        spawn_data.tag = zox_id(BlockVox);
        spawn_data.model = zox_block_vox;
        spawn_data.vox = vox;
        spawn_data.prefab_block_vox = prefab_block_vox;
    }
    byte is_name_malloc = 0;
    if (!spawn_data.name) {
        spawn_data.name = generate_name();
        is_name_malloc = 1;
    }
    ecs_entity_t e;
    if (spawn_data.vox) {
        spawn_data.prefab = prefab_block_vox_meta;
        e = spawn_block_vox_meta(world, &spawn_data);
    } else {
        spawn_data.prefab = prefab_block;
        e = spawn_block(world, &spawn_data);
    }
    if (is_name_malloc) {
        free(spawn_data.name);
    }
    return e;
}
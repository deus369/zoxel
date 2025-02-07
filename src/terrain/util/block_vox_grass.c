ecs_entity_t spawn_realm_block_vox_grass(ecs_world_t *world, const unsigned char index) {
    const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data("grass"));
    if (vox == 0) {
        zox_log(" ! grass_vox model not found.\n")
    }
    // use instanced mesh prefab
    // prefab_block_vox_meta
    SpawnBlock spawn_data = {
        .index = (unsigned char) (index + 1),
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        // .prefab_block_vox = prefab_block_vox,
        .name = "grass",
        .color = generate_random_voxel_color(),
        .tag = zox_id(BlockVox),
        .model = zox_block_vox,
        .disable_collision = 1,
        .prefab_texture = prefab_vox_texture
    };
    zox_prefab_child_named(prefab_block_vox_instanced, prefab_block_vox2)
    // zox_instance_named(prefab_block_vox_instanced, prefab_block_vox2)
    spawn_data.prefab_block_vox = prefab_block_vox2;
    zox_set(prefab_block_vox2, InstanceLink, { vox })
    // todo: spawn a new prefab here to edit - make sure its destroyed after, do we have a EntityLinkDestroyer, make this purely for generic disposal
    // add ubo to grass_vox - the vox_file object
    if (disable_block_voxes) {
        spawn_data.bake_vox = 1;
        spawn_data.vox = spawn_vox_generated_invisible(world, prefab_vox_generated, (color) { 25, 5, 5, 255 });
        spawn_data.model = 0;
        spawn_data.tag = 0;
    } else {
        spawn_data.vox = vox; //  string_hashmap_get(files_hashmap_voxes, new_string_data("grass"));
        if (!spawn_data.vox) {
            zox_log(" ! [grass] vox not found\n")
            return 0;
        }
    }
    const ecs_entity_t block_vox_meta = spawn_block_vox_meta(world, &spawn_data);
    // link instance entity here
    return block_vox_meta;
}

ecs_entity_t spawn_realm_block_vox_flower(ecs_world_t *world, const unsigned char index) {
    const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data("flower"));
    if (vox == 0) {
        zox_log(" ! vox model not found.\n")
    }
    SpawnBlock spawn_data = {
        .index = (unsigned char) (index + 1),
        .seed = generate_voxel_seed(index),
        .prefab = prefab_block_vox_meta,
        .name = "flower",
        .color = generate_random_voxel_color(),
        .tag = zox_id(BlockVox),
        .model = zox_block_vox,
        .disable_collision = 1,
        .prefab_texture = prefab_vox_texture
    };
    // zox_set(prefab_block_vox_instanced, InstanceLink, { vox })
    // const ecs_entity_t prefab_block_vox2 = prefab_block_vox_instanced;
    zox_prefab_child_named(prefab_block_vox_instanced, prefab_block_vox2)
    // zox_instance_named(prefab_block_vox_instanced, prefab_block_vox2)
    spawn_data.prefab_block_vox = prefab_block_vox2;
    zox_set(prefab_block_vox2, InstanceLink, { vox })
    // zox_prefab_set(prefab_block_vox2, TransformMatrix, { float4x4_identity() })
    #ifdef zox_disable_block_voxes
    spawn_data.bake_vox = 1;
    spawn_data.vox = spawn_vox_generated_invisible(world, prefab_vox_generated, (color) { 25, 5, 5, 255 });
    spawn_data.model = 0;
    spawn_data.tag = 0;
    #else
    spawn_data.vox = vox; //  string_hashmap_get(files_hashmap_voxes, new_string_data("grass"));
    if (!spawn_data.vox) {
        zox_log(" ! [grass] vox not found\n")
        return 0;
    }
    #endif
    const ecs_entity_t block_vox_meta = spawn_block_vox_meta(world, &spawn_data);
    // link instance entity here
    return block_vox_meta;
}


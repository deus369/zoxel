ecs_entity_t spawn_realm_block_vox_flower(ecs_world_t *world, const byte index) {
    const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data("flower"));
    if (vox == 0) {
        zox_log(" ! vox model not found.\n")
    }
    SpawnBlock spawn_data = {
        .index = (byte) (index + 1),
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

 /*else if (i == zox_block_vox_flower - 1) {
            spawn_data.name = "flower";
            spawn_data.color = generate_random_voxel_color();
#ifndef zox_disable_block_voxes
            spawn_data.tag = zox_id(BlockVox);
            spawn_data.model = zox_block_vox;
            spawn_data.prefab_block_vox = prefab_block_vox;
            const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data("flower"));
            if (!vox) {
                zox_log(" ! [flower] vox not found\n")
                continue;
            }
            spawn_data.vox = vox; // files_voxes[test_block_vox_index];
            spawn_data.disable_collision = 1;
#else
            spawn_data.bake_vox = 1;
            spawn_data.vox = vox_disabled;
#endif
        } */
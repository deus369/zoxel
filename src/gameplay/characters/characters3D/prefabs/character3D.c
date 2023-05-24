ecs_entity_t character3D_prefab;
ecs_entity_t main_character3D;
const unsigned char character3D_start_division = 0; // 1;
const int initial_character_division_addition = 1;
const int character_division_dividor = 1; // 2;

unsigned char get_character_division_from_camera(unsigned char distance_to_camera) {
    unsigned char division = 255;
    if (distance_to_camera < initial_character_division_addition + character_division_dividor) {
        division = character3D_start_division;
    } else if (distance_to_camera < initial_character_division_addition + character_division_dividor * 2) {
        division = character3D_start_division + 1;
    } else if (distance_to_camera < initial_character_division_addition + character_division_dividor * 3) {
        division = character3D_start_division + 2;
    } else if (distance_to_camera < initial_character_division_addition + character_division_dividor * 4) {
        division = character3D_start_division + 3;
    } else if (distance_to_camera < initial_character_division_addition + character_division_dividor * 5) {
        division = 4;
    }
    return division;
}

unsigned char get_character_division(int3 chunk_position, int3 camera_position) {
    unsigned char distance_to_camera = get_chunk_division(camera_position, chunk_position);
    return get_character_division_from_camera(distance_to_camera);
}

ecs_entity_t spawn_prefab_character3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_vox);
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "prefab_character3D");
    add_seed(world, e, 999);
    add_physics3D(world, e);
    zox_set(e, Bounds3D, {{ 1, 1, 1 }})
    if (!headless) {
        ecs_remove(world, e, MaterialGPULink);
        add_gpu_colors(world, e);
    }
    zox_add(e, VoxLink)
    zox_set(e, ChunkLink, { 0 })
    zox_set(e, ChunkPosition, { int3_zero })
    zox_set(e, VoxelPosition, {{ 0, 0, 0 }})
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab character3D [%lu].\n", (long int) (e));
    #endif
    character3D_prefab = e;
    return e;
}

ecs_entity_t spawn_character3D(ecs_world_t *world, ecs_entity_t prefab, vox_file *vox,
    float3 position, float4 rotation, unsigned char lod) {
    #ifdef zox_disable_characters3D
        if (main_character3D != 0) return 0;
    #endif
    // ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    zox_set(e, Position3D, { position })
    zox_set(e, Rotation3D, { rotation })
    zox_set(e, VoxLink, { main_terrain })
    #ifndef zox_disable_characters3D_voxes
        set_vox_from_vox_file(world, e, vox);
    #endif
    zox_set(e, RenderLod, { lod })
    // ecs_defer_end(world);
    main_character3D = e;
    return e;
}
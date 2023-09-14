ecs_entity_t prefab_character3D = 0;
ecs_entity_t main_character3D = 0;
const int init_character3D_lod = 1;
const int character3D_lod_dividor = 1; // 2;
const unsigned char max_character_division = 0; // 0;
int characters_count = 0;

unsigned char get_character_division_from_camera(unsigned char distance_to_camera) {
    unsigned char division = 255;
    if (distance_to_camera <= init_character3D_lod) {
        division = 0;
    } else if (distance_to_camera <= init_character3D_lod + character3D_lod_dividor * 1) {
        division = 1;
    } else if (distance_to_camera <= init_character3D_lod + character3D_lod_dividor * 2) {
        division = 2;
    } else if (distance_to_camera <= init_character3D_lod + character3D_lod_dividor * 3) {
        division = 3;
    } else if (distance_to_camera <= init_character3D_lod + character3D_lod_dividor * 4) {
        division = 4;
    }
    if (max_character_division != 0 && division < max_character_division) division = max_character_division;
    return division;
}

unsigned char get_character_division(int3 chunk_position, int3 camera_position) {
    unsigned char distance_to_camera = get_chunk_division(camera_position, chunk_position);
    return get_character_division_from_camera(distance_to_camera);
}

ecs_entity_t spawn_prefab_character3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_vox)
    zox_name("prefab_character3D")
    add_seed(world, e, 999);
    add_physics3D(world, e);
    zox_set(e, Bounds3D, {{ 1, 1, 1 }})
    zox_add(e, VoxLink)
    zox_set(e, ChunkLink, { 0 })
    zox_set(e, ChunkPosition, { int3_zero })
    zox_set(e, VoxelPosition, {{ 0, 0, 0 }})
    zox_set(e, ElementLinks, { 0, NULL})
    if (!headless) ecs_remove(world, e, MaterialGPULink);
    if (!headless) add_gpu_colors(world, e);
    ecs_defer_end(world);
    prefab_character3D = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab character3D [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_character3D(ecs_world_t *world, ecs_entity_t prefab, vox_file *vox, float3 position, float4 rotation, unsigned char lod) {
    zox_instance(prefab)
    zox_set_only(e, Position3D, { position })
    zox_set_only(e, LastPosition3D, { position })
    zox_set_only(e, Rotation3D, { rotation })
    zox_set_only(e, VoxLink, { main_terrain })
    zox_set_only(e, RenderLod, { lod })
    spawn_gpu_mesh(world, e);
    spawn_gpu_colors(world, e);
    ecs_entity_t statbar = spawn_statbar3D(world, e);
    ElementLinks elementLinks = { };
    initialize_memory_component_non_pointer(elementLinks, ecs_entity_t, 1);
    elementLinks.value[0] = statbar;
    zox_set_only(e, ElementLinks, { elementLinks.length, elementLinks.value })
    // spawn_element3D(world, e);  // spawn the uis
    #ifndef zox_disable_characters3D_voxes
        set_vox_from_vox_file(world, e, vox);
    #endif
    characters_count++;
    return e;
}
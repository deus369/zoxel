const float skybox_scale = 1024.0f;
ecs_entity_t prefab_skybox;

ecs_entity_t spawn_prefab_skybox(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_skybox");
    #ifdef zoxel_transforms3D
        add_transform3Ds(world, e);
    #endif
    #ifdef zoxel_rendering
        zox_add(e, Brightness);
        zox_set(e, MeshDirty, { 1 });
        if (!headless) {
            zox_add(e, MeshIndicies);
            zox_add(e, MeshVertices);
            set_mesh_indicies_world(world, e, cube_indicies_inverted, 36);
            set_mesh_vertices_world(world, e, cubeVertices, 24);
        }
        add_gpu_mesh(world, e);
        add_gpu_material(world, e);
    #endif
    ecs_defer_end(world);
    prefab_skybox = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" + spawned prefab skybox [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_skybox(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_skybox);
    set_unique_entity_name(world, e, "skybox");
    ecs_set(world, e, Position3D, { float3_zero });
    ecs_set(world, e, Scale1D, { skybox_scale });
    ecs_set(world, e, Brightness, { 1.0f });
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_material(world, e, shader_skybox);
    }
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" + spawned skybox [%lu]\n", (long int) e);
    #endif
    return e;
}
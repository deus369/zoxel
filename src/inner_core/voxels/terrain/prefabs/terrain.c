ecs_entity_t prefab_terrain;
ecs_entity_t main_terrain;

ecs_entity_t spawn_prefab_terrain(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_terrain")
    zox_add_tag(e, TerrainWorld)
    zox_add(e, ChunkLinks)
    #ifndef voxels_terrain_multi_material
        zox_add_tag(e, DirtTexture)
        add_texture(world, e, chunk_texture_size, 1);
        add_noise_texture(world, e);
        add_gpu_texture(world, e);
    #endif
    ecs_defer_end(world);
    prefab_terrain = e;
    return e;
}

ecs_entity_t spawn_terrain(ecs_world_t *world, ecs_entity_t prefab, float3 position, float scale) {
    ecs_defer_begin(world);
    zox_instance(prefab)
    zox_name("terrain")
    zox_set_only(e, Position3D, { position })
    zox_set_only(e, Scale1D, { scale })
    #ifndef voxels_terrain_multi_material
        spawn_gpu_material(world, e, shader3D_textured);
        spawn_gpu_texture(world, e);
    #endif
    ecs_defer_end(world);
    main_terrain = e;
    return e;
}
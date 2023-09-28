ecs_entity_t character2D_prefab;

void spawn_prefab_character2D(ecs_world_t *world, int2 textureSize) {
    ecs_defer_begin(world);
    zox_prefab()
    #ifdef zoxel_transforms2D
        add_transform2Ds(world, e);
    #endif
    #ifdef zoxel_physics2D
        zox_add_tag(e, Frictioned);
        add_physics2D(world, e);
    #endif
    // Rendering2D
    add_seed(world, e, 444);
    zox_add(e, Brightness)
    // add_dirty(world, e);
    add_texture(world, e, textureSize, 1);
    add_animated_noise_texture(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    ecs_defer_end(world);
    character2D_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab character2D [%lu].\n", (long int) (e));
    #endif
}

ecs_entity_t spawn_character2D(ecs_world_t *world, ecs_entity_t prefab, float2 position) {
    // ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    zox_instance(prefab)
    zox_set_only(e, Position2D, { position })
    zox_set_only(e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  })
    zox_set_only(e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f })
    zox_set_only(e, AnimateTexture, { (((rand() % 100) / 100.0f) * noise_animation_speed) })
    spawn_gpu_material(world, e, shader2D_textured);
    spawn_gpu_texture(world, e);
    return e;
}
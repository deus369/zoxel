ecs_entity_t character2D_prefab;

void spawn_prefab_character2D(ecs_world_t *world, int2 textureSize) {
    zox_prefab()
    zox_add_tag(e, Character2D)
    add_transform2Ds(world, e);
    zox_add_tag(e, Frictioned);
    add_physics2D(world, e);
    add_seed(world, e, 444);
    zox_add(e, Brightness)
    add_texture(world, e, textureSize, 1);
    add_animated_noise_texture(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    character2D_prefab = e;
#ifdef zoxel_debug_prefabs
    zox_log(" + spawn_prefab character2D [%lu]\n", e)
#endif
}

ecs_entity_t spawn_character2D(ecs_world_t *world, ecs_entity_t prefab, float2 position) {
    // ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    zox_instance(prefab)
    zox_set(e, Position2D, { position })
    zox_set(e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  })
    zox_set(e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f })
    zox_set(e, AnimateTexture, { (((rand() % 100) / 100.0f) * noise_animation_speed) })
    spawn_gpu_material(world, e, shader2D_textured);
    spawn_gpu_texture(world, e);
    return e;
}

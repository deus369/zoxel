ecs_entity_t character2D_prefab;

void spawn_prefab_character2D(ecs_world_t *world, const int2 textureSize) {
    zox_prefab()
    zox_add_tag(e, Character2D)
    add_transform2Ds(world, e);
    zox_add_tag(e, Frictioned);
    add_physics2D(world, e, world_grid2D_size);
    zox_add(e, Brightness)
    prefab_add_texture_generated(world, e, textureSize, zox_generate_texture_trigger);
    add_animated_noise_texture(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    character2D_prefab = e;
}

ecs_entity_t spawn_character2D(ecs_world_t *world, const ecs_entity_t prefab, const float2 position) {
    // ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    zox_instance(prefab)
    zox_set(e, Position2D, { position })
    zox_set(e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  })
    zox_set(e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f })
    zox_set(e, AnimateTexture, { (((rand() % 100) / 100.0f) * noise_animation_speed) })
    const GLuint2 shader = zox_get_value(shader_textured2D, ShaderGPULink)
    spawn_gpu_material(world, e, shader);
    spawn_gpu_texture(world, e);
    return e;
}

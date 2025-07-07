ecs_entity_t spawn_prefab_character2D(ecs_world_t *world, const int2 textureSize) {
    zox_prefab()
    zox_add_tag(e, Character2D)
    add_transform2Ds(world, e);
    zox_add_tag(e, Frictioned);
    add_physics2D(world, e, world_grid2D_size);
    zox_prefab_add(e, Brightness)
    zox_prefab_set(e, Rotation2D, { - 90 * degreesToRadians })
    // prefab_add_texture_generated(world, e, textureSize, zox_generate_texture_trigger);
    // add_animated_noise_texture(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    return e;
}

ecs_entity_t spawn_character2D(ecs_world_t *world, const ecs_entity_t prefab, const float2 position) {
    zox_instance(prefab)
    zox_set(e, Position2D, { position })
    zox_set(e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  })
    zox_set(e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f })
    // zox_set(e, AnimateTexture, { (((rand() % 100) / 100.0f) * noise_animation_speed) })
    const GLuint2 shader = zox_get_value(shader_textured2D, ShaderGPULink)
    spawn_gpu_material(world, e, shader);
    spawn_gpu_texture(world, e);
    clone_texture_to_entity(world, e, "taskbar_body");
    return e;
}

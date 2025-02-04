ecs_entity_t prefab_player_character2D;

ecs_entity_t spawn_prefab_player_character2D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_player_character2D")
    zox_add_tag(e, PlayerCharacter)
    zox_add_tag(e, PlayerCharacter2D)
    zox_prefab_set(e, CameraLink, { 0 })
    zox_prefab_set(e, DisableMovement, { 0 })
    prefab_player_character2D = e;
    return e;
}

ecs_entity_t spawn_player_character2D(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t camera) {
    const ecs_entity_t e = spawn_character2D(world, prefab, float2_zero);
    // zox_instance(prefab_player_character2D) // child prefabs don't seem to inherit tags ??
    zox_name("player_character2D")
    // zox_set(e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  })
    // zox_set(e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f })
    // const GLuint2 shader = zox_get_value(shader_textured2D, ShaderGPULink)
    // spawn_gpu_material(world, e, shader);
    // spawn_gpu_texture(world, e);
    // linking camera
    zox_set(e, CameraLink, { camera })
    zox_set(camera, CameraTarget, { e })
    zox_set(camera, Character2DLink, { e })
    return e;
}

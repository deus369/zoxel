// extern ecs_entity_t mainCamera;

//! Spawn a Player character.
ecs_entity_t spawn_player_character2D(ecs_world_t *world, ecs_entity_t camera)
{
    // child prefabs don't seem to inherit tags
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, player_character2D_prefab);
    // printf("Spawned playerCharacter2D [%lu]\n", (long unsigned int) e);
    ecs_set(world, e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  });
    ecs_set(world, e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f });
    spawn_gpu_material(world, e, textured2DShader);
    spawn_gpu_texture(world, e);
    // can be disabled
    zoxel_set(world, e, DisableMovement, { 0 });
    // make sure to link
    ecs_set(world, e, CameraLink, { camera });
    ecs_set(world, camera, CameraTarget, { e });
    ecs_set(world, camera, Character2DLink, { e });
    // ecs_add_pair(world, e, CameraLink, mainCamera);
    // ecs_add_pair(world, mainCamera, Character2DLink, e);
    return e;
}
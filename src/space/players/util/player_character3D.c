// extern ecs_entity_t mainCamera;

//! Spawn a Player character.
ecs_entity_t spawn_player_character3D(ecs_world_t *world, ecs_entity_t camera)
{
    // child prefabs don't seem to inherit tags
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, player_character3D_prefab);
    ecs_set(world, e, CameraLink, { camera });
    ecs_set(world, camera, CameraTarget, { e });
    ecs_set(world, camera, Character2DLink, { e });
    ecs_set(world, e, Scale1D, { 0.06f + ((rand() % 101) / 100.0f) * 0.04f  });
    ecs_set(world, e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f });
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, instanceShader3D);
    ecs_defer_end(world);
    // spawn_gpu_texture(world, e);
    return e;
}
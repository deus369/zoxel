extern ecs_entity_t mainCamera;

//! Spawn a Player character.
ecs_entity_t SpawnPlayerCharacter2D(ecs_world_t *world)
{
    // child prefabs don't seem to inherit tags
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, playerCharacter2DPrefab);
    // printf("Spawned playerCharacter2D [%lu]\n", (long unsigned int) e);
    ecs_set(world, e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  });
    ecs_set(world, e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f });
    SpawnGPUMaterial(world, e);
    SpawnGPUTexture(world, e);
    // can be disabled
    zoxel_set_component(world, e, DisableMovement, { 0 });
    // make sure to link
    ecs_set(world, e, CameraLink, { mainCamera });
    ecs_set(world, mainCamera, Character2DLink, { e });
    // ecs_add_pair(world, e, CameraLink, mainCamera);
    // ecs_add_pair(world, mainCamera, Character2DLink, e);
    return e;
}
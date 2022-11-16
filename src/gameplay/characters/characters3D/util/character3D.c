//! Spawn a Character2D.
ecs_entity_t spawn_character3D(ecs_world_t *world, ecs_entity_t prefab, float3 position)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    // printf("Spawned entity - character2D [%lu].\n", (long int) (e));
    // ecs_set(world, e, Position, { position });
    ecs_set(world, e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  });
    ecs_set(world, e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f });
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, instanceShader3D);
    // printf("Spawned Character2D [%lu]\n", (long unsigned int) e);
    ecs_defer_end(world);
    return e;
}
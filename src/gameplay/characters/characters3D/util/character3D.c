ecs_entity_t latest_character3D;

//! Spawn a Character3D.
ecs_entity_t spawn_character3D(ecs_world_t *world, ecs_entity_t prefab, vox_file *vox,
    float3 position, float4 rotation, float scale)
{
    ecs_defer_begin(world);
    ecs_entity_t e = spawn_voxel_chunk_mesh(world, prefab, position, scale);
    set_vox_from_vox_file(world, e, vox);
    zoxel_set(world, e, Rotation3D, { rotation });
    ecs_defer_end(world);
    latest_character3D = e;
    return e;
}

//ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
// float4 rotationer = quaternion_from_euler( (float3) { 0, 0.2f * degreesToRadians, 0 });
// zoxel_set(world, e, EternalRotation, { rotationer });

// printf("Spawned entity - character2D [%lu].\n", (long int) (e));
// ecs_set(world, e, Position3D, { position });
/*ecs_set(world, e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  });
ecs_set(world, e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f });
spawn_gpu_mesh(world, e);
spawn_gpu_material(world, e, shader3D);*/
// zoxel_log("Spawned Character3D [%lu] at [%fx%fx%f]\n", (long unsigned int) e, position.x, position.y, position.z);

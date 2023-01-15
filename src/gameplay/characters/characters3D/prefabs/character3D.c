//! Basic Character 2D prefab.
ecs_entity_t character3D_prefab;

void spawn_prefab_character3D(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_vox); // voxel_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "prefab_character3D");
    // zoxel_add_tag(world, e, NoiseChunk);
    add_seed(world, e, 999);
    // add_physics3D(world, e);
    // zoxel_add_tag(world, e, Frictioned);
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab character3D [%lu].\n", (long int) (e));
    #endif
    character3D_prefab = e;
}

// ecs_entity_t e = ecs_new_prefab(world, "character3D_prefab");
/*add_chunk(world, e, chunk_size);
add_noise_chunk(world, e);*/

/*add_seed(world, e, 444);
add_dirty(world, e);
#ifdef zoxel_transforms3D
add_transform3Ds(world, e);
#endif
#ifdef zoxel_physics3D
#endif
// Rendering3D
zoxel_add(world, e, MeshIndicies);
zoxel_add(world, e, MeshVertices);
add_gpu_mesh(world, e);
add_gpu_material(world, e);*/

/*float4 rotationer = quaternion_from_euler( (float3) { 0.1f * degreesToRadians, 0.2f * degreesToRadians, 0 });
zoxel_set(world, e, EternalRotation, { rotationer });
zoxel_add(world, e, Brightness);
add_animated_noise_texture(world, e);
add_gpu_material(world, e);
add_gpu_texture(world, e);
add_texture(world, e, textureSize);*/
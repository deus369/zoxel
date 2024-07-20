ecs_entity_t spawn_prefab_player_character3D(ecs_world_t *world) {
    zox_prefab_child(prefab_character3D)
    zox_prefab_name("prefab_character3D_player")
    zox_add_tag(e, PlayerCharacter)
    zox_add_tag(e, PlayerCharacter3D)
    // zox_add_tag(e, DisableReverseLinkChunk) // silent in chunks, chunksdont know me
    zox_prefab_set(e, CameraLink, { 0 })
    zox_prefab_set(e, PlayerLink, { 0 })
    zox_prefab_set(e, DisableMovement, { 0 })
    zox_prefab_set(e, TriggerActionA, { 0 })
    zox_prefab_set(e, TriggerActionB, { 0 })
    zox_prefab_set(e, RaycastVoxelData, { })
    // Pickups
    zox_add_tag(e, PickUpperer)
    prefab_add_sphere_collider(world, e, 0.16f);
    return e;
}

ecs_entity_2 spawn_player_character3D_in_world(ecs_world_t *world, const ecs_entity_t vox, const float3 position, const float4 rotation, const unsigned char character_lod, const ecs_entity_t player) {
    const ecs_entity_2 e = spawn_character3D(world, prefab_character3D_player, vox, position, rotation, character_lod, player, player_vox_scale, 0);
    return e;
}

/*ecs_entity_t spawn_player_character3D(ecs_world_t *world, ecs_entity_t camera) {
    // child prefabs don't seem to inherit tags
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_player_character3D);
    zox_set(e, CameraLink, { camera })
    zox_set(camera, CameraTarget, { e })
    zox_set(camera, Character2DLink, { e })
    zox_set(e, Scale1D, { 0.06f + ((rand() % 101) / 100.0f) * 0.04f  })
    zox_set(e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f })
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, shader3D);
    return e;
}
*/

ecs_entity_t spawn_prefab_player_character3D(ecs_world_t *world, const ecs_entity_t prefab) {
    if (!prefab) {
        return 0;
    }
    zox_prefab_child(prefab)
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
#ifdef zox_mod_pickups
    zox_add_tag(e, PickUpperer)
    prefab_add_sphere_collider(world, e, 0.16f);
#endif
    return e;
}

ecs_entity_t spawn_character3D_player(ecs_world_t *world, spawn_character3D_data spawn_data) {
    spawn_data.prefab = prefab_character3D_player;
    spawn_data.scale = vox_model_scale;
    // spawn_data.lod = character_lod;
    const ecs_entity_t e = spawn_character3D(world, spawn_data);
    make_test_skeleton(world, e);
    return e;
}
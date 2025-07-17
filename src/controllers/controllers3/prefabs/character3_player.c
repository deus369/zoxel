ecs_entity_t spawn_prefab_character3_player(ecs_world_t *world,
    const ecs_entity_t prefab)
{
    const float pickup_radius = 0.3f; // 0.16f
    if (!prefab) {
        return 0;
    }
    zox_prefab_child(prefab)
    zox_prefab_name("character3_player")
    zox_add_tag(e, PlayerCharacter)
    zox_add_tag(e, SaveCharacter)
    zox_prefab_set(e, CharacterSaveHash, { 0 })
    zox_prefab_set(e, Movement3, { float3_zero })
    zox_prefab_set(e, CameraLink, { 0 })
    zox_prefab_set(e, PlayerLink, { 0 })
    zox_prefab_set(e, DisableMovement, { 0 })
    zox_prefab_set(e, TriggerActionA, { 0 })
    zox_prefab_set(e, TriggerActionB, { 0 })
    zox_prefab_set(e, RaycastVoxelData, { })
    // Pickups
#ifdef zox_mod_pickups
    zox_add_tag(e, PickUpperer)
    zox_add_tag(e, SphereCollider)
    zox_prefab_set(e, SphereRadius, { pickup_radius })
    zox_prefab_set(e, CollisionDisabled, { 0 })
#endif
    return e;
}

ecs_entity_t spawn_character3D_player(ecs_world_t *world,
    spawn_character3D_data spawn_data)
{
    spawn_data.prefab = prefab_character3D_player;
    spawn_data.scale = vox_model_scale;
    // spawn_data.lod = character_lod;
    const ecs_entity_t e = spawn_character3(world, spawn_data);
    make_test_skeleton(world, e);
    zox_name("character3_player")
    return e;
}
// this is for ui raycasting
void prefab_add_raycasts_to_players(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, RaycasterTarget, { 0 })
    zox_prefab_set(e, RaycasterResult, { 0 })
    zox_prefab_set(e, Raycaster, { int2_zero })
}

// this is for world raycasting
void prefab_add_raycasts3D(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, RaycastOrigin, { float3_zero })
    zox_prefab_set(e, RaycastNormal, { float3_forward })
}

void prefab_set_game_prefabs(ecs_world_t *world) {
    prefab_add_raycasts_to_players(world, prefab_player);
    prefab_add_raycasts3D(world, prefab_camera_game);
}

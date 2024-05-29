void draw_ray_voxel_point(ecs_world_t *world, const ecs_entity_t realm, const ecs_entity_t player) {
    if (!zox_has(realm, TerrainLink)) return;
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    raycast_terrain_gizmo(world, camera, terrain);
}

void set_player_voxel_ray(ecs_world_t *world, const ecs_entity_t realm, const ecs_entity_t player, const unsigned char travel_voxel, const unsigned char voxel, unsigned char hit_type) {
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    raycast_terrain(world, camera, terrain, travel_voxel, voxel, hit_type);
}

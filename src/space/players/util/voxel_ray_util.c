// todo: when selecting pickaxe, you can destroy voxels, or with your fists
// todo: you can only place color cubes on block voxes, which drop from enemies
// todo: when placing new color in a Vox, add it to the color lookup there - unless max colors.. maybe just remove lowest color count if thats the case!
// todo: A merchant who sells color cubes
// todo: raycast a character as well
// todo: collisions to be per voxel, instead of per bounding box... that will be hard
// todo: rotational physics..!

/*void draw_ray_voxel_point(ecs_world_t *world, const ecs_entity_t realm, const ecs_entity_t player) {
    if (!zox_has(realm, TerrainLink)) return;
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    raycast_terrain_gizmo(world, camera, terrain);
}*/

/*void set_player_voxel_ray(ecs_world_t *world, const ecs_entity_t realm, const ecs_entity_t player, const unsigned char travel_voxel, const unsigned char voxel, unsigned char hit_type) {
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    raycast_terrain(world, camera, terrain, travel_voxel, voxel, hit_type);
}
*/

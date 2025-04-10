// todo: put this as a hook in game module

extern ecs_entity_t prefab_player_character2D;
extern ecs_entity_t spawn_player_character2D(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t camera);

void player_start_game2D_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    zox_set(camera, Position3D, { { 0, 0, 1 } })
    zox_set(camera, Rotation3D, { quaternion_from_euler((float3) { 0, 0 * degreesToRadians, 0 }) })
    zox_set(camera, Euler, { { 0, 0 * degreesToRadians, 0 } })
    const ecs_entity_t character = spawn_player_character2D(world, prefab_player_character2D, camera);
    zox_set(player, CharacterLink, { character })
    zox_set(character, PlayerLink, { player })
    zox_set(camera, CharacterLink, { character })
    zox_set(camera, EternalRotation, { float4_identity })
    zox_add_tag(camera, CameraFollower2D)
}

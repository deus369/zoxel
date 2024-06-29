typedef struct {
    float3 position;
    float3 euler;
    float4 rotation;
} SavePlayer;
SavePlayer player_save;
load_and_save_data(SavePlayer, player)
typedef struct {
    float3 camera_euler;
    float4 camera_rotation;
} SaveCamera;
SaveCamera camera_save;
load_and_save_data(SaveCamera, camera)

void save_player_e(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    player_save.position = zox_get_value(character, Position3D)
    player_save.euler = zox_get_value(character, Euler)
    player_save.rotation = zox_get_value(character, Rotation3D)
    save_player("zoxel", "player.dat", &player_save);
    camera_save.camera_euler = zox_get_value(camera, Euler)
    camera_save.camera_rotation = zox_get_value(camera, LocalRotation3D)
    save_camera("zoxel", "camera.dat", &camera_save);
    // zox_log(" + saved player\n")
}

void load_camera_e(ecs_world_t *world, const ecs_entity_t camera) {
    load_camera("zoxel", "camera.dat", &camera_save);
    zox_set(camera, Euler, { camera_save.camera_euler })
    zox_set(camera, LocalRotation3D, { camera_save.camera_rotation })
}

void load_character_e(ecs_world_t *world, const ecs_entity_t character) {
    load_player("zoxel", "player.dat", &player_save);
    zox_set(character, Position3D, { float3_add(player_save.position, (float3) { 0, 0.01f, 0 }) })
    zox_set(character, Euler, { player_save.euler })
    zox_set(character, Rotation3D, { player_save.rotation })
    zox_set(character, Velocity3D, { float3_zero })
    zox_set(character, Acceleration3D, { float3_zero })
}

void load_player_e(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    load_character_e(world, character);
    load_camera_e(world, camera);
}

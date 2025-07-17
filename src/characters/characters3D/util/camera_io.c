void load_camera_e(ecs_world_t *world, const ecs_entity_t camera) {
#ifdef zox_disable_save_games
    return;
#endif
    load_camera(game_name, "camera.dat", &camera_save);
    zox_set(camera, Euler, { camera_save.camera_euler })
    zox_set(camera, Rotation3D, { quaternion_from_euler(camera_save.camera_euler) })
    zox_set(camera, LocalRotation3D, { camera_save.camera_rotation_local })
    // zox_get_muter(camera, LocalRotation3D, camera_rotation3D)
    // camera_rotation3D->value = quaternion_from_euler(camera_save.camera_euler);
}
typedef struct {
    float3 camera_euler;
    float4 camera_rotation_local;
    // float4 camera_rotation;
} SaveCamera;
SaveCamera camera_save;
load_and_save_data(SaveCamera, camera)

void load_camera_e(ecs_world_t *world, const ecs_entity_t camera) {
    load_camera("zoxel", "camera.dat", &camera_save);
    zox_set(camera, Euler, { camera_save.camera_euler })
    zox_set(camera, Rotation3D, { quaternion_from_euler(camera_save.camera_euler) })
    zox_set(camera, LocalRotation3D, { camera_save.camera_rotation_local })
}

void save_camera_e(ecs_world_t *world, const ecs_entity_t camera) {
    camera_save.camera_euler = zox_get_value(camera, Euler)
    camera_save.camera_rotation_local = zox_get_value(camera, LocalRotation3D)
    save_camera("zoxel", "camera.dat", &camera_save);
}
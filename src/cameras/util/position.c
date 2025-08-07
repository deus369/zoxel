// finds closest camera to a position
entity find_closest_camera(ecs *world, const float3 position) {
    entity camera = 0;
    float closest_distance = 100000;
    for (int j = 0; j < main_cameras_count; j++) {
        const float3 camera_position = zox_get_value(main_cameras[j], Position3D)
        const float distance = float3_distance(position, camera_position);
        if (distance < closest_distance) {
            closest_distance = distance;
            camera = main_cameras[j];
        }
    }
    return camera;
}

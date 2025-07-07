extern void draw_planes(ecs_world_t *world, const plane *planes, const int plane_count)

void CameraPlanesDrawSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(CameraPlanes, cameraPlaness, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CameraPlanes, cameraPlaness, cameraPlanes)
        draw_planes(world, cameraPlanes->value, 6);
    }
} zox_declare_system(CameraPlanesDrawSystem)

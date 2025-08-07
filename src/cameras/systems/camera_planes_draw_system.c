extern void draw_planes(ecs *world, const plane *planes, const int plane_count)

void CameraPlanesDrawSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(CameraPlanes)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(CameraPlanes, cameraPlanes)
        draw_planes(world, cameraPlanes->value, 6);
    }
} zox_declare_system(CameraPlanesDrawSystem)

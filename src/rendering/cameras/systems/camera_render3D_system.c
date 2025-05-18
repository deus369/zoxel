void CameraRender3DSystem(ecs_iter_t *it) {
    camera_render_update(it, 0);
} zox_declare_system(CameraRender3DSystem)
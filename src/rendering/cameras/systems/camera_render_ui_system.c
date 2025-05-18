void CameraRenderUISystem(ecs_iter_t *it) {
    camera_render_update(it, 1);
} zox_declare_system(CameraRenderUISystem)
extern void rendering_dispose_basic_shaders3D();
extern void rendering_dispose_basic_shaders2D();
extern void load_shaders_dynamic(ecs_world_t *world);

void opengl_dispose_shaders() {
    rendering_dispose_basic_shaders2D();
    rendering_dispose_basic_shaders3D();
}

int opengl_load_shaders(ecs_world_t *world) {
    load_shaders_dynamic(world);
    return 0;
}

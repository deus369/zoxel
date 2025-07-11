#include "updates.c"

// for now until I move it all to ecs
void rendering_dispose_basic_shaders2D() {
    dispose_shader2D_instance_material();
    dispose_square_mesh();
}

// spawns after, when opengl loads
void spawn_shaders_basics2D(ecs_world_t *world) {
    spawn_material_textured2D(world);
    spawn_material_render_texture(world);
    // initialize_square_mesh_textured();
    load_instance2D_material(world);
}
entity prefab_renderer_instance;

#include "shader.c"
#include "material.c"
#include "renderer_instance.c"

void spawn_prefabs_rendering_core(ecs *world) {
    spawn_prefab_shader(world);
    spawn_prefab_material(world);
    prefab_renderer_instance = spawn_prefab_renderer_instance(world);
}
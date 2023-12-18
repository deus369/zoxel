extern void restore_opengl_resources_terrain(ecs_world_t *world);
extern ecs_entity_t main_canvas;
extern GLuint2 shader2D_textured;
extern GLuint textured2D_material;

void restore_mesh_resources(ecs_world_t *world, ecs_entity_t e) {
    if (zox_has(e, MeshGPULink)) zox_set(e, MeshGPULink, { spawn_gpu_mesh_buffers() })
    if (zox_has(e, ColorsGPULink)) zox_set(e, ColorsGPULink, { spawn_gpu_generic_buffer() })
    if (zox_has(e, UvsGPULink)) zox_set(e, UvsGPULink, { spawn_gpu_generic_buffer() })
    if (zox_has(e, MeshDirty)) zox_set(e, MeshDirty, { 1 })
}

void restore_material_resources(ecs_world_t *world, ecs_entity_t e, GLuint2 shader, GLuint material) {
    if (zox_has(e, TextureGPULink)) zox_set(e, TextureGPULink, { spawn_gpu_texture_buffers() })
    if (zox_has(e, TextureDirty)) zox_set(e, TextureDirty, { 1 })
    if (zox_has(e, MaterialGPULink) && shader.x != 0 && shader.y != 0) zox_set(e, MaterialGPULink, { spawn_gpu_material_program(shader) })
}

void restore_children_resources(ecs_world_t *world, ecs_entity_t e) {
    if (zox_has(e, Children)) {
        const Children *children = zox_get(e, Children)
        for (int i = 0; i < children->length; i++) {
            ecs_entity_t child = children->value[i];
            restore_children_resources(world, child);
            restore_material_resources(world, child, shader2D_textured, textured2D_material);
            restore_mesh_resources(world, child);
        }
    }
}

// restore opengl resources here
void restore_all_opengl_resources(ecs_world_t *world) {
    if (is_using_vulkan) return;
    zoxel_log(" > restoring all opengl resources\n");
    restore_shaders_dynamic(world);
    // rendering_restore_basic_shaders2D(world);   // replace eventually
    restore_children_resources(world, main_canvas);
    restore_opengl_resources_terrain(world);
    ecs_run(world, ecs_id(MeshGPURestoreSystem), 0, NULL);
    ecs_run(world, ecs_id(UvsGPULinkRestoreSystem), 0, NULL);
    ecs_run(world, ecs_id(ColorsGPULinkRestoreSystem), 0, NULL);
    ecs_run(world, ecs_id(MeshDirtyRestoreSystem), 0, NULL);
}

void opengl_load_resources(ecs_world_t *world) {
    if (is_using_vulkan) return;
    rendering = 1;
    skip_time_to_current();
    restore_all_opengl_resources(world);
}

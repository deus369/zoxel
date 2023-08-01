extern void restore_opengl_resources_terrain(ecs_world_t *world);
extern ecs_entity_t main_canvas;
// extern ecs_entity_t spawn_skybox(ecs_world_t *world);
extern uint2 shader_skybox;

void restore_mesh_resources(ecs_world_t *world, ecs_entity_t e) {
    if (ecs_has(world, e, MeshDirty)) zox_set_only(e, MeshDirty, { 1 })
}

void restore_material_resources(ecs_world_t *world, ecs_entity_t e, uint2 shader) {
    if (ecs_has(world, e, MaterialGPULink)) zox_set_only(e, MaterialGPULink, { spawn_gpu_material_program(shader) })
    if (ecs_has(world, e, TextureGPULink)) zox_set_only(e, TextureGPULink, { spawn_gpu_texture_buffers() })
    if (ecs_has(world, e, TextureDirty)) zox_set_only(e, TextureDirty, { 1 })
    if (ecs_has(world, e, MaterialInstancedGPULink)) zox_set_only(e, MaterialInstancedGPULink, { material2D_textured })
    // todo: restore for MaterialInstancedGPULink
}

void restore_children_resources(ecs_world_t *world, ecs_entity_t e) {
    if (ecs_has(world, e, Children)) {
        const Children *children = ecs_get(world, e, Children);
        for (int i = 0; i < children->length; i++) {
            ecs_entity_t child = children->value[i];
            restore_children_resources(world, child);
            restore_material_resources(world, child, shader2D_textured);
            restore_mesh_resources(world, child);
        }
    }
}

// restore opengl resources here
void restore_all_opengl_resources(ecs_world_t *world) {
    zoxel_log(" > restoring all opengl resources\n");
    opengl_load_shaders();
    restore_children_resources(world, main_canvas);
    restore_opengl_resources_terrain(world);
    ecs_run(world, ecs_id(MeshGPURestoreSystem), 0, NULL);
    // spawn_skybox(world);     // temp fix for now
    restore_material_resources(world, skybox, shader_skybox);
    restore_mesh_resources(world, skybox);
}
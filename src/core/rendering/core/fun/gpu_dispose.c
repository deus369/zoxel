extern void dispose_opengl_resources_terrain(ecs_world_t *world);
extern ecs_entity_t skybox;
extern ecs_entity_t main_canvas;

void dispose_material_resources(ecs_world_t *world, ecs_entity_t e) {
    if (zox_has(e, MaterialGPULink)) {
        const MaterialGPULink *materialGPULink = zox_get(e, MaterialGPULink)
        if (materialGPULink->value != 0) glDeleteProgram(materialGPULink->value);
    }
    if (zox_has(e, TextureGPULink)) {
        const TextureGPULink *textureGPULink = zox_get(e, TextureGPULink)
        if (textureGPULink->value != 0) glDeleteTextures(1, &textureGPULink->value);
    }
}

void dispose_shader_resources(ecs_world_t *world, ecs_entity_t e) {
    if (zox_has(e, ShaderGPULink)) {
        const ShaderGPULink *shaderGPULink = zox_get(e, ShaderGPULink)
        if (shaderGPULink->value.x != 0) glDeleteShader(shaderGPULink->value.x);
        if (shaderGPULink->value.y != 0) glDeleteShader(shaderGPULink->value.y);
    }
}

void dispose_mesh_resources(ecs_world_t *world, ecs_entity_t e) {
    if (zox_has(e, MeshGPULink)) {
        const MeshGPULink *meshGPULink = zox_get(e, MeshGPULink)
        if (meshGPULink->value.x != 0) glDeleteBuffers(1, &meshGPULink->value.x);
        if (meshGPULink->value.y != 0) glDeleteBuffers(1, &meshGPULink->value.y);
    }
    if (zox_has(e, UvsGPULink)) {
        const UvsGPULink *uvsGPULink = zox_get(e, UvsGPULink)
        if (uvsGPULink->value != 0) glDeleteBuffers(1, &uvsGPULink->value);
    }
    if (zox_has(e, ColorsGPULink)) {
        const ColorsGPULink *colorsGPULink = zox_get(e, ColorsGPULink)
        if (colorsGPULink->value != 0) glDeleteBuffers(1, &colorsGPULink->value);
    }
}

void dispose_children_resources(ecs_world_t *world, ecs_entity_t e) {
    if (zox_has(e, Children)) {
        const Children *children = zox_get(e, Children)
        for (int i = 0; i < children->length; i++) {
            ecs_entity_t child = children->value[i];
            dispose_children_resources(world, child);
            dispose_material_resources(world, child);
            dispose_mesh_resources(world, child);
        }
    }
}

// delete opengl resources, shaders, textures,
void delete_all_opengl_resources(ecs_world_t *world) {
    if (is_using_vulkan) return;
    zoxel_log(" > disposing all opengl resources\n");
    opengl_dispose_shaders();
    dispose_children_resources(world, main_canvas);
    dispose_opengl_resources_terrain(world);
    ecs_run(world, ecs_id(MeshGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(MeshColorsGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(MeshUvsGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(ShaderGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(MaterialGPUDisposeSystem), 0, NULL);
}

void opengl_delete_resources(ecs_world_t *world) {
    if (is_using_vulkan) return;
    rendering = 0;
    delete_all_opengl_resources(world);
}

extern void dispose_opengl_resources_terrain(ecs_world_t *world);
extern ecs_entity_t skybox;
extern ecs_entity_t main_canvas;

void dispose_material_resources(ecs_world_t *world, ecs_entity_t e) {
    if (ecs_has(world, e, MaterialGPULink)) {
        const MaterialGPULink *materialGPULink = ecs_get(world, e, MaterialGPULink);
        if (materialGPULink->value != 0) glDeleteProgram(materialGPULink->value);
    }
    if (ecs_has(world, e, TextureGPULink)) {
        const TextureGPULink *textureGPULink = ecs_get(world, e, TextureGPULink);
        if (textureGPULink->value != 0) glDeleteTextures(1, &textureGPULink->value);
    }
}

void dispose_shader_resources(ecs_world_t *world, ecs_entity_t e) {
    if (ecs_has(world, e, ShaderGPULink)) {
        const ShaderGPULink *shaderGPULink = ecs_get(world, e, ShaderGPULink);
        if (shaderGPULink->value.x != 0) glDeleteShader(shaderGPULink->value.x);
        if (shaderGPULink->value.y != 0) glDeleteShader(shaderGPULink->value.y);
    }
}

void dispose_mesh_resources(ecs_world_t *world, ecs_entity_t e) {
    if (ecs_has(world, e, MeshGPULink)) {
        const MeshGPULink *meshGPULink = ecs_get(world, e, MeshGPULink);
        if (meshGPULink->value.x != 0) glDeleteBuffers(1, &meshGPULink->value.x);
        if (meshGPULink->value.y != 0) glDeleteBuffers(1, &meshGPULink->value.y);
    }
    if (ecs_has(world, e, UvsGPULink)) {
        const UvsGPULink *uvsGPULink = ecs_get(world, e, UvsGPULink);
        if (uvsGPULink->value != 0) glDeleteBuffers(1, &uvsGPULink->value);
    }
    if (ecs_has(world, e, ColorsGPULink)) {
        const ColorsGPULink *colorsGPULink = ecs_get(world, e, ColorsGPULink);
        if (colorsGPULink->value != 0) glDeleteBuffers(1, &colorsGPULink->value);
    }
}

void dispose_children_resources(ecs_world_t *world, ecs_entity_t e) {
    if (ecs_has(world, e, Children)) {
        const Children *children = ecs_get(world, e, Children);
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
    opengl_dispose_shaders(world);
    dispose_children_resources(world, main_canvas);
    dispose_opengl_resources_terrain(world);
    ecs_run(world, ecs_id(ShaderGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(MeshGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(MeshColorsGPUDisposeSystem), 0, NULL);
    ecs_run(world, ecs_id(MeshUvsGPUDisposeSystem), 0, NULL);
    dispose_material_resources(world, skybox);
    dispose_mesh_resources(world, skybox);
}
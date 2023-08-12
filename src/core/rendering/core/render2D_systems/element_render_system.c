unsigned char renderer_layer;
const unsigned char max_render_layers = 8;

void ElementRenderSystem(ecs_iter_t *it) {
    const Position2D *position2Ds = ecs_field(it, Position2D, 2);
    const Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 3);
    const Scale1D *scale2Ds = ecs_field(it, Scale1D, 4);
    const Layer2D *layer2Ds = ecs_field(it, Layer2D, 5);
    const Brightness *brightnesses = ecs_field(it, Brightness, 6);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 7);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 8);
    const MaterialInstancedGPULink *materialGPULinks = ecs_field(it, MaterialInstancedGPULink, 9);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 10);
    const MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 11);
    opengl_enable_blend();
    for (int i = 0; i < it->count; i++) {
        const Layer2D *layer2D = &layer2Ds[i];
        if (layer2D->value != renderer_layer) continue;
        const MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value) continue; // ecs_get(it->world, it->entities[i], MeshDirty)->value) continue;
        const Position2D *position2D = &position2Ds[i];
        const Rotation2D *rotation2D = &rotation2Ds[i];
        const Scale1D *scale1D = &scale2Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const MaterialInstancedGPULink *materialInstanceGPULink = &materialGPULinks[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        render_entity_material2D_and_mesh(materialInstanceGPULink->value, meshGPULink->value, uvsGPULink->value, textureGPULink->value, ui_camera_matrix, position2D->value, rotation2D->value, scale1D->value, brightness->value, layer2D->value);
        // zoxel_log(" > rendering 2D mesh material [%lu]\n", (long int) it->entities[i]);
        // zoxel_log("     - materialInstanceGPULink: %i\n", materialInstanceGPULink->value);
    }
    opengl_disable_blend();
    opengl_unset_mesh();
    opengl_disable_texture(1);
    opengl_disable_opengl_program();
} zox_declare_system(ElementRenderSystem)

// render all ui, layer at a time
void render_ui_in_layers(ecs_world_t *world) {
    for (renderer_layer = 0; renderer_layer < max_render_layers; renderer_layer++) ecs_run(world, ecs_id(ElementRenderSystem), 0, NULL);
}

/*
float4x4 viewMatrix = ui_camera_matrix;
if (!ecs_has(it->world, it->entities[i], ElementRender)) {
    viewMatrix = render_camera_matrix;
} else {
    viewMatrix = ui_camera_matrix;
}*/
/*if (isDebugRenderMaterial2DSystem) {
    if (materialInstanceGPULink->value == 0) {
        zoxel_log("RenderMaterial2DSystem Material Error: At [%i]. Entity [%lu].\n", i, (long int) (it->entities[i]));
        continue;
    } else {
        zoxel_log("RenderMaterial2DSystem Material: At [%i]. Entity [%lu].\n", i, (long int) (it->entities[i]));
    }
}*/
extern unsigned char renderer_layer;

void RenderMeshMaterial2DSystem(ecs_iter_t *it) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    const Position2D *position2Ds = ecs_field(it, Position2D, 1);
    const Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 2);
    const Scale1D *scale2Ds = ecs_field(it, Scale1D, 3);
    const Layer2D *layer2Ds = ecs_field(it, Layer2D, 4);
    const Brightness *brightnesses = ecs_field(it, Brightness, 5);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 6);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    const MaterialInstancedGPULink *materialGPULinks = ecs_field(it, MaterialInstancedGPULink, 8);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 9);
    for (int i = 0; i < it->count; i++) {
        const Layer2D *layer2D = &layer2Ds[i];
        if (layer2D->value != renderer_layer) continue;
        const Position2D *position2D = &position2Ds[i];
        const Rotation2D *rotation2D = &rotation2Ds[i];
        const Scale1D *scale1D = &scale2Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const MaterialInstancedGPULink *materialInstanceGPULink = &materialGPULinks[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        // zoxel_log("     - materialInstanceGPULink: %i\n", materialInstanceGPULink->value);
        if (isDebugRenderMaterial2DSystem) {
            if (materialInstanceGPULink->value == 0) {
                zoxel_log("RenderMaterial2DSystem Material Error: At [%i]. Entity [%lu].\n", i, (long int) (it->entities[i]));
                continue;
            } else {
                zoxel_log("RenderMaterial2DSystem Material: At [%i]. Entity [%lu].\n", i, (long int) (it->entities[i]));
            }
        }
        float4x4 viewMatrix;
        if (!ecs_has(it->world, it->entities[i], ElementRender)) {
            viewMatrix = render_camera_matrix;
        } else {
            viewMatrix = ui_camera_matrix;
        }
        render_entity_material2D_and_mesh(materialInstanceGPULink->value, meshGPULink->value, uvsGPULink->value, textureGPULink->value, viewMatrix, position2D->value, rotation2D->value, scale1D->value, brightness->value, layer2D->value);
        // zoxel_log(" > rendering 2D mesh material [%lu]\n", (long int) it->entities[i]);
    }
    opengl_unset_mesh();
    opengl_disable_texture(1);
    opengl_disable_opengl_program();
} zox_declare_system(RenderMeshMaterial2DSystem)
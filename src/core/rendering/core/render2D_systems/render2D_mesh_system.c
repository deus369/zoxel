extern unsigned char renderer_layer;
// extern void render_entity_material2D_and_mesh(const float4x4 viewMatrix, uint2 mesh, uint material, uint texture, float2 position, float angle, float scale, float brightness, unsigned char layer);

void RenderMeshMaterial2DSystem(ecs_iter_t *it) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // zoxel_log(" > rendering uis (2) ? [%i]\n", it->count);
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
    // glBindTexture(GL_TEXTURE_2D, 0);
    opengl_disable_texture(1);
    opengl_disable_opengl_program();
} zox_declare_system(RenderMeshMaterial2DSystem)

    // const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 10);
        // const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        // if (meshIndicies2->length == 0) continue;

// if (uvsGPULink->value == 0) zoxel_log(" ! [ uvsGPULink->value is 0 ] rendering 2D mesh material [%lu]\n", (long int) it->entities[i]);
/*opengl_set_material(materialInstanceGPULink->value);
opengl_set_texture(textureGPULink->value, 0);
MaterialTextured2D attributes = initialize_material2D_textured(materialInstanceGPULink->value);
opengl_set_buffer_attributes2D(meshGPULink->value.y, uvsGPULink->value, &attributes);
glUniformMatrix4fv(attributes.view_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
glUniform1f(attributes.positionX, position2D->value.x);
glUniform1f(attributes.positionY, position2D->value.y);
glUniform1f(attributes.positionZ, ((int) layer2D->value) * shader_depth_multiplier);
glUniform1f(attributes.angle, rotation2D->value);
glUniform1f(attributes.scale, scale1D->value);
glUniform1f(attributes.brightness, brightness->value);
// opengl_set_mesh_indicies(meshGPULink->value.x);
opengl_draw_triangles(6); // meshIndicies2->length);*/
// if (uvsGPULink->value == 0) continue;
// render_entity_material2D_and_mesh(materialInstanceGPULink->value, meshGPULink->value, textureGPULink->value, viewMatrix, position2D->value, rotation2D->value, scale1D->value, brightness->value, layer2D->value);


/*void RenderMeshMaterial2DSystem(ecs_iter_t *it) {
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 2);
    Scale1D *scale2Ds = ecs_field(it, Scale1D, 3);
    Layer2D *layer2Ds = ecs_field(it, Layer2D, 4);
    Brightness *brightnesses = ecs_field(it, Brightness, 5);
    MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 6);
    MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 7);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 8);
    for (int i = 0; i < it->count; i++) {
        const Layer2D *layer2D = &layer2Ds[i];
        if (layer2D->value != renderer_layer) continue;
        const Position2D *position = &position2Ds[i];
        const Rotation2D *rotation2D = &rotation2Ds[i];
        const Scale1D *scale1D = &scale2Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        if (isDebugRenderMaterial2DSystem) {
            if (materialGPULink->value == 0) {
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
        render_entity_material2D_and_mesh(viewMatrix, meshGPULink->value, materialGPULink->value, textureGPULink->value, position->value, rotation2D->value, scale1D->value, brightness->value, layer2D->value);
        zoxel_log(" - Rendering 2D mesh material [%lu]\n", (long int) it->entities[i]);
    }
} zox_declare_system(RenderMeshMaterial2DSystem)*/

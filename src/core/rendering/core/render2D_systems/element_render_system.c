unsigned char renderer_layer;
const unsigned char max_render_layers = 8;

void ElementRenderSystem(ecs_iter_t *it) {
    unsigned char has_set_material = 0;
    const Position2D *position2Ds = ecs_field(it, Position2D, 2);
    const Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 3);
    const Layer2D *layer2Ds = ecs_field(it, Layer2D, 5);
    const Scale1D *scale2Ds = ecs_field(it, Scale1D, 4);
    const Brightness *brightnesses = ecs_field(it, Brightness, 6);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 7);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 8);
    // const MaterialInstancedGPULink *materialGPULinks = ecs_field(it, MaterialInstancedGPULink, 9);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 10);
    const MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 11);
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
        // const MaterialInstancedGPULink *materialInstanceGPULink = &materialGPULinks[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0 || uvsGPULink->value == 0 || textureGPULink->value == 0) continue;
        if (!has_set_material) {
            has_set_material = 1;
            opengl_enable_blend();
            opengl_set_material(textured2D_material);
            opengl_set_matrix(shader2D_textured_attributes.camera_matrix, render_camera_matrix);
        }
        float positionZ = ((int) layer2D->value) * shader_depth_multiplier;
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_set_buffer_attributes2D(meshGPULink->value.y, uvsGPULink->value);
        opengl_bind_texture(textureGPULink->value);
        opengl_set_float3(shader2D_textured_attributes.position, (float3) { position2D->value.x, position2D->value.y, positionZ });
        opengl_set_float(shader2D_textured_attributes.angle, rotation2D->value);
        opengl_set_float(shader2D_textured_attributes.scale, scale1D->value);
        opengl_set_float(shader2D_textured_attributes.brightness, brightness->value);
        #ifndef zox_disable_render_ui
            opengl_render(6);
        #endif
        #ifdef zoxel_catch_opengl_errors
            if (check_opengl_error_unlogged() != 0) {
                zoxel_log(" > failed to render element2D [%lu]: [%i] - [%ix%i:%i]\n", it->entities[i], 6, meshGPULink->value.x, meshGPULink->value.y); // , colorsGPULink->value);
                break;
            }
        #endif
        // zoxel_log(" > rendered element2D [%lu]: [%i] - [%ix%i:%i]\n", it->entities[i], 6, meshGPULink->value.x, meshGPULink->value.y); //, colorsGPULink->value);
    }
    if (has_set_material) {        
        opengl_disable_buffer(shader2D_textured_attributes.vertex_uv);
        opengl_disable_buffer(shader2D_textured_attributes.vertex_position);
        opengl_disable_blend();
        opengl_unset_mesh();
        opengl_disable_texture(1);
        opengl_disable_opengl_program();
    }
} zox_declare_system(ElementRenderSystem)
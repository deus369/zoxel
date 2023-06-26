// #define zoxel_render3D_uvs_system_overdebug
extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);

void Render3DTexturedSystem(ecs_iter_t *it) {
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 6);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 7);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 8);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 9);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 10);
    for (int i = 0; i < it->count; i++) {
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (meshIndicies2->length == 0) continue;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (meshGPULink->value.x == 0) continue;
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        const Position3D *position3D = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        Material3DTextured attributes = (Material3DTextured) { 
            .vertexPosition = glGetAttribLocation(materialGPULink->value, "vertexPosition"),
            .vertexUV = glGetAttribLocation(materialGPULink->value, "vertexUV"),
            .vertex_color = glGetAttribLocation(materialGPULink->value, "vertex_color"),
            .view_matrix = glGetUniformLocation(materialGPULink->value, "view_matrix"),
            .position = glGetUniformLocation(materialGPULink->value, "position"),
            .rotation = glGetUniformLocation(materialGPULink->value, "rotation"),
            .scale = glGetUniformLocation(materialGPULink->value, "scale"),
            .brightness = glGetUniformLocation(materialGPULink->value, "brightness"),
            .texture = glGetUniformLocation(materialGPULink->value, "tex"),
            .fog_data = glGetUniformLocation(materialGPULink->value, "fog_data")
        };
        opengl_set_material(materialGPULink->value);
        glUniform4f(attributes.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
        opengl_set_texture(textureGPULink->value, 0);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_shader3D_textured_set_camera_view_matrix(render_camera_matrix, &attributes);
        // opengl_set_buffer_attributes(meshGPULink->value.y, uvsGPULink->value, &attributes);
        opengl_set_buffer_attributes(meshGPULink->value.y, uvsGPULink->value, colorsGPULink->value, &attributes);
        opengl_set_material3D_uvs_properties(rotation->value, scale1D->value, brightness->value, &attributes);
        opengl_set_material3D_uvs_position(position3D->value, &attributes);
        opengl_draw_triangles(meshIndicies2->length);
        /*zoxel_log(" o> rendering mesh3D_textured [%lu]\n", it->entities[i]);
        zoxel_log("     o> materialGPULink [%i] textureGPULink [%i] meshGPULink [%ix%i] uvsGPULink [%i] colorsGPULink [%i]\n", materialGPULink->value, textureGPULink->value,
            meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value, colorsGPULink->value);
        zoxel_log("     o> scale1D [%f] position3D [%fx%fx%f] rotation [%fx%fx%fx%f]\n", scale1D->value,
            position3D->value.x, position3D->value.y, position3D->value.z, rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);*/
        // spawn_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, 0, 0.5 }), 2, 6);
    }
    opengl_unset_mesh();
    opengl_disable_texture(false);
    opengl_disable_opengl_program();
} zox_declare_system(Render3DTexturedSystem)
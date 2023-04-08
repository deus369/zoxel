extern float4x4 main_camera_matrix;

void Render3DUvsSystem(ecs_iter_t *it) {
    #ifdef zoxel_time_render_3d_uvs
        begin_timing_absolute()
    #endif
    // check_opengl_error("[pre Render3DUvsSystem Error]");
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 6);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 7);
    #ifdef voxels_terrain_multi_material
        const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 8);
        const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 9);
    #else
        const VoxLink *voxLinks = ecs_field(it, VoxLink, 8);
    #endif
    // later store commands per material to optimize this process
    // zoxel_log("rendering chunks: %i\n", it->count);
    unsigned char has_set_single_material = 0;
    ecs_entity_t vox_entity = 0;
    const MaterialGPULink *materialGPULink;
    for (int i = 0; i < it->count; i++) {
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (meshIndicies2->length == 0) {
            continue;
        }
        const Position3D *position3D = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        #ifdef voxels_terrain_multi_material
            const MaterialGPULink *materialGPULink = &materialGPULinks[i];
            const TextureGPULink *textureGPULink = &textureGPULinks[i];
        #endif
        #ifndef voxels_terrain_multi_material
            const VoxLink *voxLink = &voxLinks[i];
            if (vox_entity != voxLink->value) {
                vox_entity = voxLink->value;
                materialGPULink = ecs_get(it->world, voxLink->value, MaterialGPULink);
            }
            // const MaterialGPULink *materialGPULink = ecs_get(it->world, voxLink->value, MaterialGPULink);
            Material3DTextured attributes = (Material3DTextured) { 
                glGetAttribLocation(materialGPULink->value, "vertexPosition"),
                glGetAttribLocation(materialGPULink->value, "vertexUV"), 0,
                glGetUniformLocation(materialGPULink->value, "position"), 0, 0, 0, 0
            };
            if (!has_set_single_material) {
                has_set_single_material = 1;
                const TextureGPULink *textureGPULink = ecs_get(it->world, voxLink->value, TextureGPULink);
                attributes.view_matrix = glGetUniformLocation(materialGPULink->value, "view_matrix");
                attributes.rotation = glGetUniformLocation(materialGPULink->value, "rotation");
                attributes.scale = glGetUniformLocation(materialGPULink->value, "scale");
                attributes.brightness = glGetUniformLocation(materialGPULink->value, "brightness");
                opengl_set_material(materialGPULink->value);
                //    check_opengl_error("[opengl_set_material Error]");
                opengl_set_texture(textureGPULink->value, false);
                //    check_opengl_error("[opengl_set_texture Error]");
                opengl_shader3D_textured_set_camera_view_matrix(main_camera_matrix, &attributes);
                //    check_opengl_error("[opengl_shader3D_textured_set_camera_view_matrix Error]");
                opengl_set_material3D_uvs_properties(rotation->value, scale1D->value, brightness->value, &attributes);
                //    check_opengl_error("[opengl_set_material3D_uvs_properties Error]");
            }
            opengl_set_material3D_uvs_position(position3D->value, &attributes);
            //    check_opengl_error("[opengl_set_material3D_uvs_position Error]");
            opengl_set_buffer_attributes(meshGPULink->value.y, uvsGPULink->value, &attributes);
            //    check_opengl_error("[opengl_set_buffer_attributes Error]");
            opengl_set_mesh_indicies(meshGPULink->value.x);
            //    check_opengl_error("[opengl_set_mesh_indicies Error]");
            opengl_draw_triangles(meshIndicies2->length);
            //    check_opengl_error("[opengl_draw_triangles Error]");
        #else
            Material3DTextured attributes = (Material3DTextured) { 
                glGetAttribLocation(materialGPULink->value, "vertexPosition"),
                glGetAttribLocation(materialGPULink->value, "vertexUV"),
                glGetUniformLocation(materialGPULink->value, "view_matrix"),
                glGetUniformLocation(materialGPULink->value, "position"),
                glGetUniformLocation(materialGPULink->value, "rotation"),
                glGetUniformLocation(materialGPULink->value, "scale"),
                glGetUniformLocation(materialGPULink->value, "brightness"),
                glGetUniformLocation(materialGPULink->value, "tex")
            };
            opengl_set_material(materialGPULink->value);
            opengl_set_texture_only(textureGPULink->value);
            opengl_set_mesh_indicies(meshGPULink->value.x);
            opengl_shader3D_textured_set_camera_view_matrix(main_camera_matrix, &attributes);
            opengl_set_buffer_attributes(meshGPULink->value.y, uvsGPULink->value, &attributes);
            opengl_set_material3D_uvs_properties(rotation->value, scale1D->value, brightness->value, &attributes);
            opengl_set_material3D_uvs_position(position3D->value, &attributes);
            opengl_draw_triangles(meshIndicies2->length);
        #endif
    }
    opengl_unset_mesh();
    opengl_disable_texture(false);
    opengl_disable_opengl_program();
    #ifdef ANDROID_BUILD
        check_opengl_error("[render3D_uvs_system Error]");
    #endif
    #ifdef zoxel_time_render_3d_uvs
        end_timing("Render3DUvsSystem")
    #endif
}
zoxel_declare_system(Render3DUvsSystem)
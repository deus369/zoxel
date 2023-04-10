// #define zoxel_render3D_uvs_system_overdebug
extern float4x4 main_camera_matrix;

void Render3DUvsSystem(ecs_iter_t *it) {
    #ifdef zoxel_time_render_3d_uvs
        begin_timing_absolute()
    #endif
    #ifdef zoxel_render3D_uvs_system_overdebug
        check_opengl_error("[pre render3D_uvs_system Error]");
        GLint memory_used, memory_total;
        glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &memory_used);
        glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &memory_total);
    #endif
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
                attributes.fog_data = glGetUniformLocation(materialGPULink->value, "fog_data");
                attributes.view_matrix = glGetUniformLocation(materialGPULink->value, "view_matrix");
                attributes.rotation = glGetUniformLocation(materialGPULink->value, "rotation");
                attributes.scale = glGetUniformLocation(materialGPULink->value, "scale");
                attributes.brightness = glGetUniformLocation(materialGPULink->value, "brightness");
                opengl_set_material(materialGPULink->value);
                glUniform4f(attributes.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
                opengl_set_texture(textureGPULink->value, false);
                opengl_shader3D_textured_set_camera_view_matrix(main_camera_matrix, &attributes);
                opengl_set_material3D_uvs_properties(rotation->value, scale1D->value, brightness->value, &attributes);
            }
            opengl_set_buffer_attributes(meshGPULink->value.y, uvsGPULink->value, &attributes);
            //    check_opengl_error("[opengl_set_buffer_attributes Error]");
            opengl_set_mesh_indicies(meshGPULink->value.x);
            opengl_set_material3D_uvs_position(position3D->value, &attributes);
            //    check_opengl_error("[opengl_set_material3D_uvs_position Error]");
            opengl_draw_triangles(meshIndicies2->length);
            #ifdef zoxel_render3D_uvs_system_overdebug
                if (check_opengl_error("[render3D_uvs_system opengl_draw_triangles Error]")) {
                    zoxel_log(" !!! indicies length is: %i\n", meshIndicies2->length);
                    zoxel_log(" !!! GPU Memory Usage [%d MB / %d MB]\n", memory_used / 1024, memory_total / 1024);
                }
            #endif
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
    #ifdef zoxel_render3D_uvs_system_overdebug
        check_opengl_error("[render3D_uvs_system Error]");
    #endif
    #ifdef zoxel_time_render_3d_uvs
        end_timing("Render3DUvsSystem")
    #endif
}
zoxel_declare_system(Render3DUvsSystem)
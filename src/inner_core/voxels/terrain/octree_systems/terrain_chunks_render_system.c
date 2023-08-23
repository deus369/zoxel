// #define zoxel_render3D_uvs_system_overdebug
// later store commands per material to optimize this process

void TerrainChunksRenderSystem(ecs_iter_t *it) {
    #ifdef zoxel_time_render_3d_uvs
        begin_timing_absolute()
    #endif
    #ifdef zoxel_render3D_uvs_system_overdebug
        check_opengl_error("[pre render3D_uvs_system Error]");
        GLint memory_used, memory_total;
        glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &memory_used);
        glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &memory_total);
    #endif
    ecs_world_t *world = it->world;
    int rendered_count = 0;
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 6);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 7);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 8);
    const VoxLink *voxLinks = ecs_field(it, VoxLink, 9);
    unsigned char has_set_material = 0;
    ecs_entity_t vox_entity = 0;
    const MaterialGPULink *materialGPULink;
    const TextureGPULink *textureGPULink;
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
        const VoxLink *voxLink = &voxLinks[i];
        if (vox_entity != voxLink->value) {
            vox_entity = voxLink->value;
            const TilemapLink *tilemapLink = ecs_get(world, voxLink->value, TilemapLink);
            materialGPULink = ecs_get(world, tilemapLink->value, MaterialGPULink);
            if (materialGPULink->value == 0) break;
            textureGPULink = ecs_get(world, tilemapLink->value, TextureGPULink);
            if (textureGPULink->value == 0) break;
        }
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(materialGPULink->value);
            opengl_shader3D_textured_set_camera_view_matrix(render_camera_matrix, &attributes_textured3D);
            glUniform4f(attributes_textured3D.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
            opengl_bind_texture(textureGPULink->value);
            opengl_set_material3D_uvs_properties(rotation->value, scale1D->value, brightness->value, &attributes_textured3D);
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(attributes_textured3D.vertex_position, meshGPULink->value.y);
        opengl_enable_uv_buffer(attributes_textured3D.vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(attributes_textured3D.vertex_color, colorsGPULink->value);
        glUniform3f(attributes_textured3D.position, position3D->value.x, position3D->value.y, position3D->value.z);
        #ifndef zox_disable_render_terrain_chunks
            opengl_render(meshIndicies2->length);
            /*if (check_opengl_error("[render_terrain]")) {
                zoxel_log("     -> i (%i), rendered (%i), entity [%lu], length [%i], gpu links [%i] x [%i]\n", i, rendered_count, it->entities[i], meshIndicies2->length, meshGPULink->value.x, meshGPULink->value.y);
                return;
            }*/
        #endif
        #ifdef zoxel_render3D_uvs_system_overdebug
            if (check_opengl_error("[render3D_uvs_system opengl_render Error]")) {
                zoxel_log(" !!! indicies length is: %i\n", meshIndicies2->length);
                zoxel_log(" !!! GPU Memory Usage [%d MB / %d MB]\n", memory_used / 1024, memory_total / 1024);
            }
        #endif
        rendered_count++;
    }
    if (has_set_material) {
        opengl_unset_mesh();
        opengl_disable_texture(false);
        opengl_disable_opengl_program();
    }
    #ifdef zoxel_render3D_uvs_system_overdebug
        check_opengl_error("[render3D_uvs_system Error]");
    #endif
    #ifdef zoxel_time_render_3d_uvs
        end_timing("TerrainChunksRenderSystem")
    #endif
    // if (rendered_count > 0) zoxel_log(" > rendered chunks [%i]\n", rendered_count);
} zox_declare_system(TerrainChunksRenderSystem)

        /*#ifdef voxels_terrain_multi_material
            const MaterialGPULink *materialGPULink = &materialGPULinks[i];
            const TextureGPULink *textureGPULink = &textureGPULinks[i];
        #endif*/
        //#ifndef voxels_terrain_multi_material
        /*#else
            Material3DTextured attributes = (Material3DTextured) { 
                glGetAttribLocation(materialGPULink->value, "vertex_position"),
                glGetAttribLocation(materialGPULink->value, "vertex_uv"),
                glGetUniformLocation(materialGPULink->value, "camera_matrix"),
                glGetUniformLocation(materialGPULink->value, "position"),
                glGetUniformLocation(materialGPULink->value, "rotation"),
                glGetUniformLocation(materialGPULink->value, "scale"),
                glGetUniformLocation(materialGPULink->value, "brightness"),
                glGetUniformLocation(materialGPULink->value, "tex")
            };
            opengl_set_material(materialGPULink->value);
            opengl_bind_texture(textureGPULink->value);
            opengl_set_mesh_indicies(meshGPULink->value.x);
            opengl_shader3D_textured_set_camera_view_matrix(render_camera_matrix, &attributes);
            opengl_set_buffer_attributes(meshGPULink->value.y, uvsGPULink->value, &attributes);
            opengl_set_material3D_uvs_properties(rotation->value, scale1D->value, brightness->value, &attributes);
            opengl_set_material3D_uvs_position(position3D->value, &attributes);
            opengl_render(meshIndicies2->length);
        #endif*/
/*#ifdef voxels_terrain_multi_material
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 9);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 10);
#else*/
//#endif
            /*attributes = (Material3DTextured) { 
                glGetAttribLocation(materialGPULink->value, "vertex_position"),
                glGetAttribLocation(materialGPULink->value, "vertex_uv"),
                glGetAttribLocation(materialGPULink->value, "vertex_color"), 0,
                glGetUniformLocation(materialGPULink->value, "position"), 0, 0, 0, 0
            };
            attributes.fog_data = glGetUniformLocation(materialGPULink->value, "fog_data");
            attributes.camera_matrix = glGetUniformLocation(materialGPULink->value, "camera_matrix");
            attributes.rotation = glGetUniformLocation(materialGPULink->value, "rotation");
            attributes.scale = glGetUniformLocation(materialGPULink->value, "scale");
            attributes.brightness = glGetUniformLocation(materialGPULink->value, "brightness");*/
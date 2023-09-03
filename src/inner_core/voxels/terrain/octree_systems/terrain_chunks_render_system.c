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
            opengl_set_matrix(attributes_textured3D.camera_matrix, render_camera_matrix);
            opengl_bind_texture(textureGPULink->value);
            glUniform4f(attributes_textured3D.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
            opengl_set_material3D_uvs_properties(rotation->value, scale1D->value, brightness->value, &attributes_textured3D);
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(attributes_textured3D.vertex_position, meshGPULink->value.y);
        opengl_enable_uv_buffer(attributes_textured3D.vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(attributes_textured3D.vertex_color, colorsGPULink->value);
        glUniform3f(attributes_textured3D.position, position3D->value.x, position3D->value.y, position3D->value.z);
        #ifndef zox_disable_render_terrain_chunks
            opengl_render(meshIndicies2->length);
            // opengl_render(36);
        #endif
        #ifdef zoxel_catch_opengl_errors
            if (check_opengl_error_unlogged() != 0) {
                zoxel_log(" > could not render terrain [%i]: indicies [%i] - [%ix%i:%i]\n", rendered_count, meshIndicies2->length, meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value);
                break;
            }
        #endif
        rendered_count++;
    }
    if (has_set_material) {
        opengl_disable_buffer(attributes_textured3D.vertex_color);
        opengl_disable_buffer(attributes_textured3D.vertex_uv);
        opengl_disable_buffer(attributes_textured3D.vertex_position);
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

/*#ifdef zoxel_render3D_uvs_system_overdebug
    if (check_opengl_error("[render3D_uvs_system opengl_render Error]")) {
        zoxel_log(" !!! indicies length is: %i\n", meshIndicies2->length);
        zoxel_log(" !!! GPU Memory Usage [%d MB / %d MB]\n", memory_used / 1024, memory_total / 1024);
    }
#endif*/
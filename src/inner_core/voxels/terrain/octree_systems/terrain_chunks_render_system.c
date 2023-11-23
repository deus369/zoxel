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
    unsigned char has_set_material = 0;
    ecs_entity_t vox_entity = 0;
    const MaterialGPULink *materialGPULink;
    const TextureGPULink *textureGPULink;
    zox_iter_world()
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    //const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    //const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 6);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 7);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 8);
    const VoxLink *voxLinks = ecs_field(it, VoxLink, 9);
    const Textured3DAttributes *attributes_textured3D = get_textured3D_material_attributes(world);
    for (int i = 0; i < it->count; i++) {
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (!meshIndicies2->length) continue;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (!meshGPULink->value.x) continue;
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        const Position3D *position3D = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        //const Scale1D *scale1D = &scale1Ds[i];
        //const Brightness *brightness = &brightnesses[i];
        const VoxLink *voxLink = &voxLinks[i];
        if (vox_entity != voxLink->value) {
            vox_entity = voxLink->value;
            const TilemapLink *tilemapLink = zox_get(voxLink->value, TilemapLink)
            materialGPULink = zox_get(tilemapLink->value, MaterialGPULink)
            if (!materialGPULink->value) continue;
            textureGPULink = zox_get(tilemapLink->value, TextureGPULink)
            if (!textureGPULink->value) continue;
        }
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(materialGPULink->value);
            opengl_set_matrix(attributes_textured3D->camera_matrix, render_camera_matrix);
            opengl_set_float4(attributes_textured3D->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
            opengl_set_float4(attributes_textured3D->rotation, rotation->value);
            opengl_set_float(attributes_textured3D->scale, 0.5f);
            opengl_set_float(attributes_textured3D->brightness, 1);
#ifndef zox_disable_terrain_textures
            opengl_bind_texture(textureGPULink->value);
#endif
        }
        opengl_set_float3(attributes_textured3D->position, position3D->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(attributes_textured3D->vertex_position, meshGPULink->value.y);
#ifndef zox_disable_terrain_textures
        opengl_enable_uv_buffer(attributes_textured3D->vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(attributes_textured3D->vertex_color, colorsGPULink->value);
#endif
#ifndef zox_disable_render_terrain_chunks
        opengl_render(meshIndicies2->length);
#endif
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged()) {
            zox_log(" > could not render terrain [%i]: indicies [%i] - [%ix%i]\n", i, meshIndicies2->length, meshGPULink->value.x, meshGPULink->value.y);
            // zox_log(" > could not render terrain [%i]: indicies [%i] - [%ix%i:%i]\n", rendered_count, meshIndicies2->length, meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value);
            break;
        }
#endif
    }
    if (has_set_material) {
#ifndef zox_disable_terrain_textures
        opengl_disable_buffer(attributes_textured3D->vertex_color);
        opengl_disable_buffer(attributes_textured3D->vertex_uv);
#endif
        opengl_disable_buffer(attributes_textured3D->vertex_position);
        opengl_unset_mesh();
#ifndef zox_disable_terrain_textures
        opengl_disable_texture(false);
#endif
        opengl_disable_opengl_program();
    }
#ifdef zoxel_render3D_uvs_system_overdebug
    check_opengl_error("[render3D_uvs_system Error]");
#endif
#ifdef zoxel_time_render_3d_uvs
    end_timing("TerrainChunksRenderSystem")
#endif
} zox_declare_system(TerrainChunksRenderSystem)

/*#ifdef zoxel_render3D_uvs_system_overdebug
    if (check_opengl_error("[render3D_uvs_system opengl_render Error]")) {
        zoxel_log(" !!! indicies length is: %i\n", meshIndicies2->length);
        zoxel_log(" !!! GPU Memory Usage [%d MB / %d MB]\n", memory_used / 1024, memory_total / 1024);
    }
#endif*/
// zoxel_log(" > get_textured3D_material_value [%i]\n", get_textured3D_material_value(world));
// zoxel_log(" > textureGPULink [%i]\n", textureGPULink->value);
// glUniform3f(attributes_textured3D->position, position3D->value.x, position3D->value.y, position3D->value.z);

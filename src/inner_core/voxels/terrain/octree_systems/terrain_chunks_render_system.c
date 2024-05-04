// #define zoxel_render3D_uvs_system_overdebug
// later store commands per material to optimize this process
void TerrainChunksRenderSystem(ecs_iter_t *it) {
    unsigned char has_set_material = 0;
    ecs_entity_t vox_entity = 0;
    const MaterialGPULink *materialGPULink;
    const TextureGPULink *textureGPULink;
    const MaterialTextured3D *attributes_textured3D;
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_in(MeshGPULink, meshGPULinks, 3)
    zox_field_in(UvsGPULink, uvsGPULinks, 4)
    zox_field_in(ColorsGPULink, colorsGPULinks, 5)
    zox_field_in(MeshIndicies, meshIndiciess, 6)
    zox_field_in(VoxLink, voxLinks, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(MeshIndicies, meshIndiciess, meshIndicies)
        if (!meshIndicies->length) continue;
        zox_field_i_in(MeshGPULink, meshGPULinks, meshGPULink)
        if (!meshGPULink->value.x) continue;
        zox_field_i_in(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        zox_field_i_in(UvsGPULink, uvsGPULinks, uvsGPULink)
        zox_field_i_in(ColorsGPULink, colorsGPULinks, colorsGPULink)
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(Rotation3D, rotation3Ds, rotation3D)
        if (vox_entity != voxLink->value) {
            vox_entity = voxLink->value;
            const TilemapLink *tilemapLink = zox_get(voxLink->value, TilemapLink)
            materialGPULink = zox_get(tilemapLink->value, MaterialGPULink)
            if (!materialGPULink->value) continue;
            textureGPULink = zox_get(tilemapLink->value, TextureGPULink)
            if (!textureGPULink->value) continue;
            attributes_textured3D = zox_get(tilemapLink->value, MaterialTextured3D)
            if (!attributes_textured3D) break;
        }
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(materialGPULink->value);
            opengl_set_matrix(attributes_textured3D->camera_matrix, render_camera_matrix);
            opengl_set_float4(attributes_textured3D->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
            opengl_set_float4(attributes_textured3D->rotation, rotation3D->value);
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
        opengl_render(meshIndicies->length);
#endif
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged()) {
            zox_log(" > could not render terrain [%i]: indicies [%i] - [%ix%i]\n", i, meshIndicies->length, meshGPULink->value.x, meshGPULink->value.y);
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
} zox_declare_system(TerrainChunksRenderSystem)

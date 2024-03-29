extern unsigned char can_render_ui(ecs_world_t *world, ecs_entity_t e);
// #define zox_time_render3D_textured_system

void Element3DRenderSystem(ecs_iter_t *it) {
#ifdef zox_disable_render_element3D
    return;
#endif
#ifdef zox_time_render3D_textured_system
    begin_timing()
#endif
    unsigned char has_set_material = 0;
    zox_iter_world()
    const Textured3DAttributes *attributes_textured3D = get_textured3D_material_attributes(world);
    const Position3D *position3Ds = ecs_field(it, Position3D, 2);
    const Rotation3D *rotation3Ds = ecs_field(it, Rotation3D, 3);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 6);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 8);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 9);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 10);
    for (int i = 0; i < it->count; i++) {
        ecs_entity_t e = it->entities[i];
        if (!can_render_ui(world, e)) continue;
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (!meshIndicies2->length) continue;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (!meshGPULink->value.x || !meshGPULink->value.y) continue;
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        const Position3D *position3D = &position3Ds[i];
        const Rotation3D *rotation3D = &rotation3Ds[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(get_textured3D_material_value(world));
            opengl_set_matrix(attributes_textured3D->camera_matrix, render_camera_matrix);
            opengl_set_float4(attributes_textured3D->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
            opengl_set_float(attributes_textured3D->scale, 1);
            opengl_set_float(attributes_textured3D->brightness, 1);
            // scale1D->value, brightness->value
        }
        opengl_set_float3(attributes_textured3D->position, position3D->value);
        opengl_set_float4(attributes_textured3D->rotation, rotation3D->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(attributes_textured3D->vertex_position, meshGPULink->value.y);
#ifndef zox_disable_terrain_textures
        opengl_enable_uv_buffer(attributes_textured3D->vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(attributes_textured3D->vertex_color, colorsGPULink->value);
        opengl_bind_texture(textureGPULink->value);
#endif
#ifndef zox_disable_render_ui_3D
        opengl_render(meshIndicies2->length);
#endif
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged()) {
            zoxel_log(" > failed to render element3D [%i]: [%i] - [%ix%i:%i]\n", i, meshIndicies2->length, meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value);
            break;
        }
#endif
#ifdef zox_time_render3D_textured_system
        did_do_timing()
#endif
    }
    if (has_set_material) {
#ifdef zox_disable_terrain_textures
        opengl_disable_buffer(attributes_textured3D->vertex_color);
        opengl_disable_buffer(attributes_textured3D->vertex_uv);
#endif
        opengl_disable_buffer(attributes_textured3D->vertex_position);
#ifdef zox_disable_terrain_textures
        opengl_disable_texture(false);
#endif
        opengl_unset_mesh();
        opengl_disable_opengl_program();
    }
#ifdef zox_time_render3D_textured_system
    end_timing("    - render3D_textured_system")
#endif
} zox_declare_system(Element3DRenderSystem)

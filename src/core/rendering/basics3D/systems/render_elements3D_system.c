// this for 3D uis
// #define zox_time_render3D_textured_system
extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
extern unsigned char can_render_ui(ecs_world_t *world, ecs_entity_t e);
unsigned char has_rendered_elements = 0;
// todo: this produces a memory leak on newer nvidia driver... not sure why

void RenderElements3DSystem(ecs_iter_t *it) {
    #ifdef zox_time_render3D_textured_system
        begin_timing()
    #endif
    ecs_world_t *world = it->world;
    const Textured3DAttributes *attributes_textured3D = get_textured3D_material_attributes(world);
    unsigned char has_set_material = 0;
    int rendered_count = 0;
    const Position3D *positions = ecs_field(it, Position3D, 2);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 3);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 6);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 8);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 9);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 10);
    for (int i = 0; i < it->count; i++) {
        if (!can_render_ui(it->world, it->entities[i])) continue;
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (meshIndicies2->length == 0) continue;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        const Position3D *position3D = &positions[i];
        const Rotation3D *rotation3D = &rotations[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(get_textured3D_material_value(world));
            opengl_set_matrix(attributes_textured3D->camera_matrix, render_camera_matrix);
            opengl_set_float4(attributes_textured3D->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, fog_density });
            opengl_set_float(attributes_textured3D->scale, 1);
            opengl_set_float(attributes_textured3D->brightness, 1);
            // scale1D->value, brightness->value
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(attributes_textured3D->vertex_position, meshGPULink->value.y);
        opengl_enable_uv_buffer(attributes_textured3D->vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(attributes_textured3D->vertex_color, colorsGPULink->value);
        opengl_bind_texture(textureGPULink->value);
        opengl_set_float3(attributes_textured3D->position, position3D->value);
        opengl_set_float4(attributes_textured3D->rotation, rotation3D->value);
        // glUniform3f(attributes_textured3D->position, position3D->value.x, position3D->value.y, position3D->value.z);
        // glUniform4f(attributes_textured3D->rotation, rotation3D->value.x, rotation3D->value.y, rotation3D->value.z, rotation3D->value.w);
        #ifndef zox_disable_render_ui_3D
            opengl_render(meshIndicies2->length);
        #endif
        #ifdef zoxel_catch_opengl_errors
            if (check_opengl_error_unlogged() != 0) {
                zoxel_log(" > failed to render element3D [%lu]: [%i] - [%ix%i:%i]\n", it->entities[i], meshIndicies2->length, meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value);
                break;
            }
        #endif
        #ifdef zox_time_render3D_textured_system
            did_do_timing()
        #endif
        rendered_count++;
    }
    if (has_set_material) {
        opengl_disable_buffer(attributes_textured3D->vertex_color);
        opengl_disable_buffer(attributes_textured3D->vertex_uv);
        opengl_disable_buffer(attributes_textured3D->vertex_position);
        opengl_unset_mesh();
        opengl_disable_texture(false);
        opengl_disable_opengl_program();
    }
    #ifdef zox_time_render3D_textured_system
        end_timing("    - render3D_textured_system")
        // zoxel_log("         > count [%i]\n", it->count);
    #endif
    #ifdef zox_errorcheck_render_ui_3D
        if (rendered_count > 0) zoxel_log(" > rendered elements [%i]\n", rendered_count);
    #endif
} zox_declare_system(RenderElements3DSystem)
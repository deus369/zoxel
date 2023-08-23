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
    // check_opengl_error("[pre render_elements error]");
    // if (has_rendered_elements) return;
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
        // if (uvsGPULink->value == 0) continue;
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        // if (colorsGPULink->value == 0) continue;
        const Position3D *position3D = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(textured3D_material);
            opengl_shader3D_textured_set_camera_view_matrix(render_camera_matrix, &attributes_textured3D);
            glUniform4f(attributes_textured3D.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
            opengl_set_material3D_uvs_properties(rotation->value, 1, 1, &attributes_textured3D);
            // scale1D->value, brightness->value
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(attributes_textured3D.vertex_position, meshGPULink->value.y);
        opengl_enable_uv_buffer(attributes_textured3D.vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(attributes_textured3D.vertex_color, colorsGPULink->value);
        opengl_bind_texture(textureGPULink->value);
        glUniform3f(attributes_textured3D.position, position3D->value.x, position3D->value.y, position3D->value.z);
        glUniform4f(attributes_textured3D.rotation, rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);
        #ifndef zox_disable_render_ui_3D
            // zoxel_log("     -> i (%i), rendering (%i), entity [%lu], length [%i], gpu links (%i) [%i] x [%i]\n", i, rendered_count, it->entities[i], meshIndicies2->length, textured3D_material, meshGPULink->value.x, meshGPULink->value.y);
            opengl_render(meshIndicies2->length);
            // glDrawElements(GL_TRIANGLES, meshIndicies2->length, GL_UNSIGNED_INT, meshIndicies2->value);
            #ifdef zox_errorcheck_render_ui_3D
                if (check_opengl_error("[render_elements]")) {
                    // zoxel_log("     -> i (%i), rendered (%i), entity [%lu], length [%i], gpu links (%i) [%i] x [%i]\n", i, rendered_count, it->entities[i], meshIndicies2->length, textured3D_material, meshGPULink->value.x, meshGPULink->value.y);
                    return;
                }
            #endif
        #endif
        #ifdef zox_time_render3D_textured_system
            did_do_timing()
        #endif
        rendered_count++;
        // if (!has_rendered_elements) has_rendered_elements = 1;
    }
    if (has_set_material) {
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

// const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
// const Brightness *brightnesses = ecs_field(it, Brightness, 4);
// const Scale1D *scale1D = &scale1Ds[i];
// const Brightness *brightness = &brightnesses[i];
/*zoxel_log(" o> rendering mesh3D_textured [%lu]\n", it->entities[i]);
zoxel_log("     o> materialGPULink [%i] textureGPULink [%i] meshGPULink [%ix%i] uvsGPULink [%i] colorsGPULink [%i]\n", materialGPULink->value, textureGPULink->value,
    meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value, colorsGPULink->value);
zoxel_log("     o> scale1D [%f] position3D [%fx%fx%f] rotation [%fx%fx%fx%f]\n", scale1D->value,
    position3D->value.x, position3D->value.y, position3D->value.z, rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);*/
// spawn_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, 0, 0.5 }), 2, 6);
void opengl_upload_mesh_colors(GLuint2 mesh_buffer, GLuint color_buffer, const int *indicies, int indicies_length, const float3 *verts, const color_rgb *color_rgbs, int verts_length) {
#ifdef zox_characters_as_cubes
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indicies), cube_indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#else
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(color_rgb), color_rgbs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
#ifdef zoxel_catch_opengl_errors
    check_opengl_error("opengl_upload_mesh_colors");
#endif
}

void MeshUpdateCharacters3DSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    zox_field_out(MeshIndicies, meshIndiciess, 3)
    zox_field_out(MeshVertices, meshVerticess, 4)
    zox_field_out(MeshColorRGBs, meshColorRGBss, 5)
    zox_field_out(MeshDirty, meshDirtys, 2)
    zox_field_out(MeshGPULink, meshGPULinks, 6)
    zox_field_out(ColorsGPULink, colorsGPULinks, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value == 0) continue;
        zox_field_i_in(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_i_in(MeshVertices, meshVerticess, meshVertices)
        zox_field_i_in(MeshColorRGBs, meshColorRGBss, meshColorRGBs)
        zox_field_i_out(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i_out(ColorsGPULink, colorsGPULinks, colorsGPULink)
        meshDirty->value = 0;
#ifndef zox_characters_as_cubes
        if (meshIndicies->length == 0) {
            // clear mesh and colors buffer if zero again
            if (meshGPULink->value.x != 0 && meshGPULink->value.y != 0 && colorsGPULink->value != 0) {
                clear_regular_buffer(&meshGPULink->value.x);
                clear_regular_buffer(&meshGPULink->value.y);
                clear_regular_buffer(&colorsGPULink->value);
            }
            continue;
        }
        if (meshGPULink->value.x == 0 && meshGPULink->value.y == 0 && colorsGPULink->value == 0) {
            meshGPULink->value.x = spawn_gpu_generic_buffer();
            meshGPULink->value.y = spawn_gpu_generic_buffer();
            colorsGPULink->value = spawn_gpu_generic_buffer();
        }
#endif
        opengl_upload_mesh_colors(meshGPULink->value, colorsGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices->value, meshColorRGBs->value, meshVertices->length);
#ifdef zox_errorcheck_render_characters_3D
        zoxel_log(" + character mesh gpu uploaded [%ix%i:%i] -> indicies [%i]\n", meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value, meshIndicies->length);
#endif
    }
} zox_declare_system(MeshUpdateCharacters3DSystem)

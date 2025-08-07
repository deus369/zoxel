void opengl_upload_mesh_colors(uint2 mesh_buffer, uint color_buffer, const int *indicies, int indicies_length, const float3 *verts, const color_rgb *color_rgbs, int verts_length) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(color_rgb), color_rgbs, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#ifdef zoxel_catch_opengl_errors
    check_opengl_error("opengl_upload_mesh_colors");
#endif
}

void MeshUpdateCharacters3DSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(MeshIndicies)
    zox_sys_in(MeshVertices)
    zox_sys_in(MeshColorRGBs)
    zox_sys_in(MeshDirty)
    zox_sys_out(MeshGPULink)
    zox_sys_out(ColorsGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshDirty, meshDirty)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshVertices, meshVertices)
        zox_sys_i(MeshColorRGBs, meshColorRGBs)
        zox_sys_o(MeshGPULink, meshGPULink)
        zox_sys_o(ColorsGPULink, colorsGPULink)
        if (meshDirty->value != mesh_state_upload) {
            continue;
        }
        if (meshIndicies->length == 0) {
            // clear mesh and colors buffer if zero again
            if (meshGPULink->value.x != 0 && meshGPULink->value.y != 0 && colorsGPULink->value != 0) {
                clear_regular_buffer(&meshGPULink->value.x);
                clear_regular_buffer(&meshGPULink->value.y);
            }
            if (colorsGPULink->value) clear_regular_buffer(&colorsGPULink->value);
            continue;
        }
        if (meshGPULink->value.x == 0 && meshGPULink->value.y == 0) {
            meshGPULink->value.x = spawn_gpu_generic_buffer();
            meshGPULink->value.y = spawn_gpu_generic_buffer();
        }
        if (colorsGPULink->value == 0) {
            colorsGPULink->value = spawn_gpu_generic_buffer();
        }
        // zox_log(" + Uploading mesh [%i : %i]\n", meshVertices->length, meshColorRGBs->length)
        opengl_upload_mesh_colors(meshGPULink->value, colorsGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices->value, meshColorRGBs->value, meshVertices->length);
#ifdef zox_errorcheck_render_characters_3D
        zox_log(" + character mesh gpu uploaded [%ix%i:%i] -> indicies [%i]\n", meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value, meshIndicies->length);
#endif
    }
} zox_declare_system(MeshUpdateCharacters3DSystem)
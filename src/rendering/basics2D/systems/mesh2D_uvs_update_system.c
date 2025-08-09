void opengl_upload_shader2D_textured(uint2 mesh_buffer, uint uv_buffer, const int *indicies, int indicies_length, const float2 *verts, const float2 *uvs, int verts_length) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float2), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float2), uvs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#ifdef zoxel_catch_opengl_errors
    if (check_opengl_error("opengl_upload_shader2D_textured")) {
        zox_log("     > [%ix%i:%i]\n", mesh_buffer.x, mesh_buffer.y, uv_buffer);
    }
#endif
}

void Mesh2DUvsUpdateSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(MeshIndicies)
    zox_sys_in(MeshVertices2D)
    zox_sys_in(MeshUVs)
    zox_sys_in(MeshGPULink)
    zox_sys_in(UvsGPULink)
    zox_sys_in(MeshDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshDirty, meshDirty)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(UvsGPULink, uvsGPULink)
        zox_sys_i(MeshVertices2D, meshVertices2D)
        zox_sys_i(MeshUVs, meshUVs)
        if (meshDirty->value != mesh_state_upload) {
            continue;
        }
        if (!meshIndicies->length | !meshGPULink->value.x || !meshGPULink->value.y | !uvsGPULink->value) {
            // not every layout element has a mesh!
            // zox_sys_world()
            // zox_log_error("[%s] uploaded mesh2D_uvs failed due to [%s]", zox_get_name(it->entities[i]), !meshIndicies->length ? "no mesh" : "no gpu links")
            continue;
        }
        opengl_upload_shader2D_textured(meshGPULink->value, uvsGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices2D->value, meshUVs->value, meshVertices2D->length);
    }
} zoxd_system(Mesh2DUvsUpdateSystem)

void update_shader3D_textured(const uint2 mesh_buffer, const uint uv_buffer, const uint color_buffer, const int *indicies, int indicies_length, const float3 *verts, const int verts_length, const float2 *uvs, const color_rgb *color_rgbs) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float2), uvs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(color_rgb), color_rgbs, GL_STATIC_DRAW);
#ifdef zoxel_catch_opengl_errors
    check_opengl_error("opengl_upload_shader3D_textured");
#endif
}

void Mesh3DTexturedUploadSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(MeshIndicies)
    zox_sys_in(MeshVertices)
    zox_sys_in(MeshUVs)
    zox_sys_in(MeshColorRGBs)
    zox_sys_in(MeshGPULink)
    zox_sys_in(UvsGPULink)
    zox_sys_in(ColorsGPULink)
    zox_sys_in(MeshDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshDirty, meshDirty)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(UvsGPULink, uvsGPULink)
        zox_sys_i(ColorsGPULink, colorsGPULink)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshVertices, meshVertices)
        zox_sys_i(MeshUVs, meshUVs)
        zox_sys_i(MeshColorRGBs, meshColorRGBs)
        if (meshDirty->value != mesh_state_upload) {
            continue;
        }
        if (!meshGPULink->value.x || !meshGPULink->value.y || !uvsGPULink->value || !colorsGPULink->value || !meshIndicies->length || !meshVertices->length || !meshUVs->length) {
            continue;
        }
        if (meshVertices->length != meshUVs->length) {
            zox_field_world()
            zox_field_e()
            zox_log_error("[%s] mesh verts [%i] / uvs [%i] missmatch", zox_get_name(e), meshVertices->length, meshUVs->length)
            continue;
        }
        update_shader3D_textured(meshGPULink->value, uvsGPULink->value, colorsGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices->value, meshVertices->length, meshUVs->value, meshColorRGBs->value);
    }
} zox_declare_system(Mesh3DTexturedUploadSystem)
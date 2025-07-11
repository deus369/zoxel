void update_shader3D_textured(const GLuint2 mesh_buffer, const GLuint uv_buffer, const GLuint color_buffer, const int *indicies, int indicies_length, const float3 *verts, const int verts_length, const float2 *uvs, const color_rgb *color_rgbs) {
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
    zox_field_in(MeshIndicies, meshIndiciess, 1)
    zox_field_in(MeshVertices, meshVerticess, 2)
    zox_field_in(MeshUVs, meshUVss, 3)
    zox_field_in(MeshColorRGBs, meshColorRGBss, 4)
    zox_field_in(MeshGPULink, meshGPULinks, 5)
    zox_field_in(UvsGPULink, uvsGPULinks, 6)
    zox_field_in(ColorsGPULink, colorsGPULinks, 7)
    zox_field_in(MeshDirty, meshDirtys, 8)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value != mesh_state_upload) {
            continue;
        }
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i(UvsGPULink, uvsGPULinks, uvsGPULink)
        zox_field_i(ColorsGPULink, colorsGPULinks, colorsGPULink)
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_i(MeshVertices, meshVerticess, meshVertices)
        zox_field_i(MeshUVs, meshUVss, meshUVs)
        zox_field_i(MeshColorRGBs, meshColorRGBss, meshColorRGBs)
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
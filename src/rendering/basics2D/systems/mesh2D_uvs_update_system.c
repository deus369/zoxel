void opengl_upload_shader2D_textured(GLuint2 mesh_buffer, GLuint uv_buffer, const int *indicies, int indicies_length, const float2 *verts, const float2 *uvs, int verts_length) {
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

void Mesh2DUvsUpdateSystem(ecs_iter_t *it) {
    zox_field_in(MeshIndicies, meshIndiciess, 1)
    zox_field_in(MeshVertices2D, meshVertices2Ds, 2)
    zox_field_in(MeshUVs, meshUVss, 3)
    zox_field_in(MeshGPULink, meshGPULinks, 4)
    zox_field_in(UvsGPULink, uvsGPULinks, 5)
    zox_field_in(MeshDirty, meshDirtys, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value != mesh_state_upload) {
            continue;
        }
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i(UvsGPULink, uvsGPULinks, uvsGPULink)
        if (!meshIndicies->length | !meshGPULink->value.x || !meshGPULink->value.y | !uvsGPULink->value) {
            zox_field_world()
            zox_log_error("[%s] uploaded mesh2D_uvs failed", zox_get_name(it->entities[i]))
            continue;
        }
        zox_field_i(MeshVertices2D, meshVertices2Ds, meshVertices2D)
        zox_field_i(MeshUVs, meshUVss, meshUVs)
        opengl_upload_shader2D_textured(meshGPULink->value, uvsGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices2D->value, meshUVs->value, meshVertices2D->length);
    }
} zox_declare_system(Mesh2DUvsUpdateSystem)

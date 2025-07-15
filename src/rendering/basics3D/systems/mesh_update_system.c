void opengl_upload_mesh(uint2 mesh, uint material, const int *indicies, int indicies_length, const float3 *verts, int verts_length) {
    GLint vertex_attribute_position = glGetAttribLocation(material, "vertex_position");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glEnableVertexAttribArray(vertex_attribute_position);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(vertex_attribute_position, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshUpdateSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(MeshDirty)
    zox_sys_in(MeshIndicies)
    zox_sys_in(MeshVertices)
    zox_sys_in(MeshGPULink)
    zox_sys_in(MaterialGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshDirty, meshDirty)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(MaterialGPULink, materialGPULink)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshVertices, meshVertices)
        if (meshDirty->value != mesh_state_upload) {
            continue;
        }
        opengl_upload_mesh(meshGPULink->value, materialGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices->value, meshVertices->length);
    }
} zox_declare_system(MeshUpdateSystem)

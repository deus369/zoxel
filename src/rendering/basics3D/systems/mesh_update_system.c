void opengl_upload_mesh(GLuint2 mesh, GLuint material, const int *indicies, int indicies_length, const float3 *verts, int verts_length) {
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
    // if (!ecs_query_changed(NULL, it)) return;
    zox_field_in(MeshDirty, meshDirtys, 1)
    zox_field_in(MeshIndicies, meshIndiciess, 2)
    zox_field_in(MeshVertices, meshVerticess, 3)
    zox_field_in(MeshGPULink, meshGPULinks, 4)
    zox_field_in(MaterialGPULink, materialGPULinks, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value != mesh_state_upload) continue;
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i(MaterialGPULink, materialGPULinks, materialGPULink)
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_i(MeshVertices, meshVerticess, meshVertices)
        opengl_upload_mesh(meshGPULink->value, materialGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices->value, meshVertices->length);
    }
} zox_declare_system(MeshUpdateSystem)

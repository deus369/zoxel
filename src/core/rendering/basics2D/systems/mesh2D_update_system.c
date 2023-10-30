void set_gpu_mesh2D(GLuint2 mesh, GLuint material, const int *indicies, int indicies_length, const float2 *verts, int verts_length) {
    // Material3D material3D = spawn_material3D_properties(material);
    GLint vertex_shader_index = 0;
    int float_per_data = 2;
    int floats_length = verts_length * float_per_data;
    float combined_verts[floats_length];
    for (int i = 0; i < verts_length; i++) {
        float2 vert = verts[i];
        combined_verts[i * float_per_data + 0] = vert.x;
        combined_verts[i * float_per_data + 1] = vert.y;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * 4, indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glEnableVertexAttribArray(vertex_shader_index);
    glBufferData(GL_ARRAY_BUFFER, floats_length * 4, combined_verts, GL_STATIC_DRAW);
    glVertexAttribPointer(vertex_shader_index, 2, GL_FLOAT, GL_FALSE, 4 * float_per_data, (GLvoid*)(0 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh2DUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices2D *meshVertices = ecs_field(it, MeshVertices2D, 3);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 4);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 5);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 1) continue;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        const MeshVertices2D *meshVertices2 = &meshVertices[i];
        set_gpu_mesh2D(meshGPULink->value, materialGPULink->value, meshIndicies2->value, meshIndicies2->length, meshVertices2->value, meshVertices2->length);
        meshDirty->value = 0;
        // zox_log("   > mesh2D updated: %lu\n", it->entities[i])
    }
} zox_declare_system(Mesh2DUpdateSystem)

void Mesh2DInstancedUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices2D *meshVertices = ecs_field(it, MeshVertices2D, 3);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 4);
    const MaterialInstancedGPULink *materialGPULinks = ecs_field(it, MaterialInstancedGPULink, 5);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 1) continue;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialInstancedGPULink *materialGPULink = &materialGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        const MeshVertices2D *meshVertices2 = &meshVertices[i];
        set_gpu_mesh2D(meshGPULink->value, materialGPULink->value, meshIndicies2->value, meshIndicies2->length, meshVertices2->value, meshVertices2->length);
        meshDirty->value = 0;
        // zox_log("   > mesh2D instanced updated: %lu\n", it->entities[i])
    }
} zox_declare_system(Mesh2DInstancedUpdateSystem)

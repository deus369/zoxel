void MeshUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 4);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 5);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 1) continue;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        const MeshVertices *meshVertices2 = &meshVertices[i];
        opengl_upload_mesh(meshGPULink->value, materialGPULink->value, meshIndicies2->value, meshIndicies2->length, meshVertices2->value, meshVertices2->length);
        meshDirty->value = 0;
    }
} zox_declare_system(MeshUpdateSystem)
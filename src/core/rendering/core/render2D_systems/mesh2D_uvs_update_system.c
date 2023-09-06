void Mesh2DUvsUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices2D *meshVertices = ecs_field(it, MeshVertices2D, 3);
    const MeshUVs *meshUVs = ecs_field(it, MeshUVs, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 6);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 1) continue;
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (meshIndicies2->length == 0) continue;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        if (uvsGPULink->value == 0) continue;
        const MeshVertices2D *meshVertices2 = &meshVertices[i];
        const MeshUVs *meshUVs2 = &meshUVs[i];
        opengl_upload_shader2D_textured(meshGPULink->value, uvsGPULink->value, meshIndicies2->value, meshIndicies2->length, meshVertices2->value, meshUVs2->value, meshVertices2->length);
        meshDirty->value = 0;
    }
} zox_declare_system(Mesh2DUvsUpdateSystem)
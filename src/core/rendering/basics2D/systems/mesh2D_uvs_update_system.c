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
        if (!meshDirty->value) continue;
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (!meshIndicies2->length) continue;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (!meshGPULink->value.x || !meshGPULink->value.y) continue;
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        if (!uvsGPULink->value) continue;
        const MeshVertices2D *meshVertices2D = &meshVertices[i];
        const MeshUVs *meshUVs2 = &meshUVs[i];
        opengl_upload_shader2D_textured(meshGPULink->value, uvsGPULink->value, meshIndicies2->value, meshIndicies2->length, meshVertices2D->value, meshUVs2->value, meshVertices2D->length);
        meshDirty->value = 0;
        // zox_log("   > mesh2D with uvs updated: %lu [%f]\n", it->entities[i], meshVertices2D->value[2].x)
    }
} zox_declare_system(Mesh2DUvsUpdateSystem)

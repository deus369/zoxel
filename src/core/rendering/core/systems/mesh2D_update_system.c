
void Mesh2DUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) {
        return;
    }
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices2D *meshVertices = ecs_field(it, MeshVertices2D, 3);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 4);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 5);
    // printf("TextureUpdateSystem [%i] \n", it->count);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 1) {
            continue;
        }
        meshDirty->value = 0;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        const MeshVertices2D *meshVertices2 = &meshVertices[i];
        set_gpu_mesh2D(meshGPULink->value, materialGPULink->value,
            meshIndicies2->value, meshIndicies2->length,
            meshVertices2->value, meshVertices2->length);
    }
}
zoxel_declare_system(Mesh2DUpdateSystem)

void MeshColorsUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) {
        return;
    }
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    const MeshColors *meshColors = ecs_field(it, MeshColors, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value == 1) {
            meshDirty->value = 0;
            const MeshGPULink *meshGPULink = &meshGPULinks[i];
            const MaterialGPULink *materialGPULink = &materialGPULinks[i];
            const MeshIndicies *meshIndicies2 = &meshIndicies[i];
            const MeshVertices *meshVertices2 = &meshVertices[i];
            const MeshColors *meshColors2 = &meshColors[i];
            if (meshColors2->length != meshVertices2->length) {
                // printf("Issue with %i mesh colors.\n", i);
                continue;
            }
            set_gpu_mesh_colors(meshGPULink->value, materialGPULink->value, meshIndicies2->value, meshIndicies2->length,
                meshVertices2->value, meshVertices2->length, meshColors2->value);
        }
    }
}
zoxel_declare_system(MeshColorsUpdateSystem)
//! Generate random noise texture.
/**
 * Once main thread is fixed, update to gpu in this system.
 * \todo update to gpu here?
*/
void MeshUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    const MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 4);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 5);
    // printf("TextureUpdateSystem [%i] \n", it->count);
    for (int i = 0; i < it->count; i++)
    {
        const MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 1)
        {
            continue;
        }
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        const MeshVertices *meshVertices2 = &meshVertices[i];
        set_gpu_mesh(meshGPULink->value,  materialGPULink->value,
            meshIndicies2->value, meshIndicies2->length,
            meshVertices2->value, meshVertices2->length);
    }
}
zoxel_declare_system(MeshUpdateSystem)
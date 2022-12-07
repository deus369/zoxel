//! Generate random noise texture.
/**
 * Once main thread is fixed, update to gpu in this system.
 * \todo update to gpu here?
*/
void MeshUpdateSystem(ecs_iter_t *it)
{
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
ECS_SYSTEM_DECLARE(MeshUpdateSystem);

/*printf("MeshUpdateSystem [%i - %i] Material [%i] \n", meshGPULink->value.x, meshGPULink->value.y, materialGPULink->value);
for (int j = 0; j < 8; j++)
{
    printf("    - Vertex [%i] is [%fx%fx%f]\n", j, meshVertices2->value[j].x,  meshVertices2->value[j].y, meshVertices2->value[j].z);
}*/
/*for (int j = 0; j < meshIndicies->length; j++)
{
    printf("        - Index [%i] is [%i]\n", j, meshIndicies->value[j]);
}
for (int j = 0; j < meshVertices->length; j++)
{
    printf("        - Vertex [%i] is [%f]\n", j, meshVertices->value[j]);
}*/
//! Not a proper queue yet.
#ifndef maxQueue
#define maxQueue 512
#endif
int meshUpdateQueueCount = 0;
const MeshIndicies* meshIndiciesQueue[maxQueue];
const MeshVertices* meshVerticesQueue[maxQueue];
GLuint2 meshGPULinksQueue[maxQueue];
GLuint materialsQueue[maxQueue];

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
    const EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 4);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 5);
    // printf("TextureUpdateSystem [%i] \n", it->count);
    for (int i = 0; i < it->count; i++)
    {
        const EntityDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value != 1)
        {
            continue;
        }
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        const MeshVertices *meshVertices2 = &meshVertices[i];
        meshGPULinksQueue[meshUpdateQueueCount] = meshGPULink->value;
        materialsQueue[meshUpdateQueueCount] = materialGPULink->value;
        meshIndiciesQueue[meshUpdateQueueCount] = meshIndicies2;
        meshVerticesQueue[meshUpdateQueueCount] = meshVertices2;
        /*printf("MeshUpdateSystem [%i - %i] Material [%i] \n", meshGPULink->value.x, meshGPULink->value.y, materialGPULink->value);
        for (int j = 0; j < 8; j++)
        {
            printf("    - Vertex [%i] is [%fx%fx%f]\n", j, meshVertices2->value[j].x,  meshVertices2->value[j].y, meshVertices2->value[j].z);
        }*/
        meshUpdateQueueCount++;
    }
}
ECS_SYSTEM_DECLARE(MeshUpdateSystem);

//! \todo Make proper queue.
void MeshUpdateMainThread()
{
    if (meshUpdateQueueCount == 0)
    {
        return;
    }
    // printf("queueCount: %i \n", queueCount);
    for (int i = meshUpdateQueueCount - 1; i >= 0; i--)
    {
        const GLuint2 meshGPULink = meshGPULinksQueue[i];
        const GLuint material = materialsQueue[i];
        const MeshIndicies *meshIndicies = meshIndiciesQueue[i];
        const MeshVertices *meshVertices = meshVerticesQueue[i];
        set_gpu_mesh(meshGPULink, material, meshIndicies->value, meshIndicies->length, meshVertices->value, meshVertices->length);
        /*printf("Updating Mesh [%i - %i] Material [%i] \n", meshGPULink.x, meshGPULink.y, material);
        for (int j = 0; j < meshIndicies->length; j++)
        {
            printf("        - Index [%i] is [%i]\n", j, meshIndicies->value[j]);
        }
        for (int j = 0; j < meshVertices->length; j++)
        {
            // printf("        - Vertex [%i] is [%fx%fx%f]\n", j, meshVertices->value[j].x,  meshVertices->value[j].y, meshVertices->value[j].z);
            printf("        - Vertex [%i] is [%f]\n", j, meshVertices->value[j]);
        }*/
    }
    meshUpdateQueueCount = 0;
}
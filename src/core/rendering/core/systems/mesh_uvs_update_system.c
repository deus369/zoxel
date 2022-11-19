//! Not a proper queue yet.
int meshUvsUpdateQueueCount = 0;
GLuint2 meshUvsGPULinksQueue[maxMeshQueue];
GLuint materialsUvsQueue[maxMeshQueue];
GLuint uvsGPULinksQueue[maxMeshQueue];
const MeshIndicies* meshUvsIndiciesQueue[maxMeshQueue];
const MeshVertices* meshUvsVerticesQueue[maxMeshQueue];
const MeshUVs* meshUvsQueue[maxMeshQueue];

//! Generate random noise texture.
/**
 * Once main thread is fixed, update to gpu in this system.
 * \todo update to gpu here?
*/
void MeshUvsUpdateSystem(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    const MeshDirty *entityDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    const MeshUVs *meshUVs = ecs_field(it, MeshUVs, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    // printf("TextureUpdateSystem [%i] \n", it->count);
    for (int i = 0; i < it->count; i++)
    {
        const MeshDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value != 1)
        {
            continue;
        }
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        const MeshVertices *meshVertices2 = &meshVertices[i];
        const MeshUVs *meshUVs2 = &meshUVs[i];
        meshUvsGPULinksQueue[meshUvsUpdateQueueCount] = meshGPULink->value;
        materialsUvsQueue[meshUvsUpdateQueueCount] = materialGPULink->value;
        uvsGPULinksQueue[meshUvsUpdateQueueCount] = uvsGPULink->value;
        meshUvsIndiciesQueue[meshUvsUpdateQueueCount] = meshIndicies2;
        meshUvsVerticesQueue[meshUvsUpdateQueueCount] = meshVertices2;
        meshUvsQueue[meshUvsUpdateQueueCount] = meshUVs2;
        // printf("MeshUvsUpdateSystem [%i - %i] Material [%i] \n", meshGPULink->value.x, meshGPULink->value.y, materialGPULink->value);
        /*for (int j = 0; j < 8; j++)
        {
            printf("    - Vertex [%i] is [%fx%fx%f]\n", j, meshVertices2->value[j].x,  meshVertices2->value[j].y, meshVertices2->value[j].z);
        }*/
        meshUvsUpdateQueueCount++;
    }
}
ECS_SYSTEM_DECLARE(MeshUvsUpdateSystem);

//! \todo Make proper queue.
void mesh_uvs_update_main_thread()
{
    if (meshUvsUpdateQueueCount == 0)
    {
        return;
    }
    // printf("queueCount: %i \n", queueCount);
    for (int i = meshUvsUpdateQueueCount - 1; i >= 0; i--)
    {
        const GLuint2 meshGPULink = meshUvsGPULinksQueue[i];
        const GLuint material = materialsUvsQueue[i];
        // const GLuint uvs = uvsGPULinksQueue[i];
        const MeshIndicies *meshIndicies = meshUvsIndiciesQueue[i];
        const MeshVertices *meshVertices = meshUvsVerticesQueue[i];
        const MeshUVs *meshUVs = meshUvsQueue[i];
        opengl_upload_shader3D_textured(meshGPULink, material, meshIndicies->value, meshIndicies->length, meshVertices->value,
            meshVertices->length, meshUVs->value, meshUVs->length);
        
        // printf("Updating Mesh [%i - %i] Material [%i] \n", meshGPULink.x, meshGPULink.y, material);
        /*for (int j = 0; j < meshIndicies->length; j++)
        {
            printf("        - Index [%i] is [%i]\n", j, meshIndicies->value[j]);
        }
        for (int j = 0; j < meshVertices->length; j++)
        {
            printf("        - Vertex [%i] is [%f]\n", j, meshVertices->value[j]);
        }*/
    }
    meshUvsUpdateQueueCount = 0;
}
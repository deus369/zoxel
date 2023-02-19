// #define zoxel_time_mesh_uvs_update_system

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
    #ifdef zoxel_time_mesh_uvs_update_system
        begin_timing()
    #endif
    const MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    const MeshUVs *meshUVs = ecs_field(it, MeshUVs, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
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
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        const MeshVertices *meshVertices2 = &meshVertices[i];
        const MeshUVs *meshUVs2 = &meshUVs[i];
        opengl_upload_shader3D_textured(
            meshGPULink->value, uvsGPULink->value, materialGPULink->value,
            meshIndicies2->value, meshIndicies2->length,
            meshVertices2->value, meshVertices2->length, meshUVs2->value);
        //if (meshIndicies2->length != 0)
        // {
            //if (it->entities[i] == 1597)
            //    printf("Added %lu - %i - tri_count[%i] \n",  it->entities[i], meshIndicies2->length / 3, tri_count);
        // }
        #ifdef zoxel_time_mesh_uvs_update_system
            did_do_timing()
        #endif
    }
    #ifdef zoxel_time_mesh_uvs_update_system
        end_timing("MeshUvsUpdateSystem")
    #endif
}
zoxel_declare_system(MeshUvsUpdateSystem)

/*void MeshUvsUpdateSystem2(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    const MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    MeshUVs *meshUVs = ecs_field(it, MeshUVs, 4);
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
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        MeshUVs *meshUVs2 = &meshUVs[i];
        opengl_upload_shader3D_textured(
            meshGPULink->value, uvsGPULink->value, materialGPULink->value,
            meshIndicies2->value, meshIndicies2->length,
            meshVertices2->value, meshVertices2->length,
            meshUVs2->value, meshUVs2->length);
        free(meshIndicies2->value);
        meshIndicies2->value = NULL;
        meshIndicies2->length = 0;
        free(meshVertices2->value);
        meshVertices2meshVertices2->value = NULL;
        meshIndicies2->length = 0;
        free(meshUVs2->value);
        meshUVs2->value = NULL;
        meshUVs2->length = 0;
    }
}
zoxel_declare_system(MeshUvsUpdateSystem2)*/
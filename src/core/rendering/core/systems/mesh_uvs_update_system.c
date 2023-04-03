// Once main thread is fixed, update to gpu in this system.
// todo: update this in thread
void MeshUvsUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) {
        return;
    }
    #ifdef zoxel_time_mesh_uvs_update_system
        begin_timing()
        int update_count = 0;
    #endif
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    const MeshUVs *meshUVs = ecs_field(it, MeshUVs, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value == 1) {
        /*if (meshDirty->value == 1) {
            meshDirty->value = 2;
        } else if (meshDirty->value == 2) {*/
            meshDirty->value = 0;
            const MeshGPULink *meshGPULink = &meshGPULinks[i];
            const MaterialGPULink *materialGPULink = &materialGPULinks[i];
            const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
            const MeshIndicies *meshIndicies2 = &meshIndicies[i];
            const MeshVertices *meshVertices2 = &meshVertices[i];
            const MeshUVs *meshUVs2 = &meshUVs[i];
            opengl_upload_shader3D_textured(meshGPULink->value, uvsGPULink->value, materialGPULink->value,
                meshIndicies2->value, meshIndicies2->length, meshVertices2->value, meshVertices2->length, meshUVs2->value);
            #ifdef zoxel_time_mesh_uvs_update_system
                did_do_timing()
                update_count++;
            #endif
        }
    }
    #ifdef zoxel_time_mesh_uvs_update_system
        end_timing("    - mesh_uvs_update_system")
        if (did_do) {
            zoxel_log("        - updated chunk meshes [%i]\n", update_count);
        }
    #endif
}
zoxel_declare_system(MeshUvsUpdateSystem)
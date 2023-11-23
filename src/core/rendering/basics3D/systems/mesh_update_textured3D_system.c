void MeshUpdateTextured3DSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
#ifdef zoxel_time_mesh_uvs_update_system
    int update_count = 0;
    begin_timing()
#endif
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 6);
    const MeshUVs *meshUVs = ecs_field(it, MeshUVs, 4);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    const MeshColorRGBs *meshColorRGBs = ecs_field(it, MeshColorRGBs, 5);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 8);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (!meshDirty->value) continue;
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        const MeshVertices *meshVertices2 = &meshVertices[i];
        const MeshUVs *meshUVs2 = &meshUVs[i];
        const MeshColorRGBs *meshColorRGBs2 = &meshColorRGBs[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        opengl_upload_shader3D_textured(meshGPULink->value, uvsGPULink->value, colorsGPULink->value, meshIndicies2->value, meshIndicies2->length, meshVertices2->value, meshVertices2->length, meshUVs2->value, meshColorRGBs2->value);
        meshDirty->value = 0;
#ifdef zoxel_time_mesh_uvs_update_system
        did_do_timing()
        update_count++;
#endif
    }
#ifdef zoxel_time_mesh_uvs_update_system
    end_timing("    - mesh_uvs_update_system")
    if (did_do) zox_log("        - updated chunk meshes [%i]\n", update_count)
#endif
} zox_declare_system(MeshUpdateTextured3DSystem)

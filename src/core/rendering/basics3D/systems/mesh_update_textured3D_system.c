void MeshUpdateTextured3DSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
#ifdef zoxel_time_mesh_uvs_update_system
    int update_count = 0;
    begin_timing()
#endif
    zox_field_in(MeshIndicies, meshIndiciess, 2)
    zox_field_in(MeshVertices, meshVerticess, 3)
    zox_field_in(MeshUVs, meshUVss, 4)
    zox_field_in(MeshColorRGBs, meshColorRGBss, 5)
    zox_field_in(MeshGPULink, meshGPULinks, 6)
    zox_field_in(UvsGPULink, uvsGPULinks, 7)
    zox_field_in(ColorsGPULink, colorsGPULinks, 8)
    zox_field_out(MeshDirty, meshDirtys, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(MeshDirty, meshDirtys, meshDirty)
        if (!meshDirty->value) continue;
        zox_field_i_in(MeshGPULink, meshGPULinks, meshGPULink)
        // zox_field_i_in(MaterialGPULink, materialGPULinks, materialGPULink)
        zox_field_i_in(UvsGPULink, uvsGPULinks, uvsGPULink)
        zox_field_i_in(ColorsGPULink, colorsGPULinks, colorsGPULink)
        zox_field_i_in(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_i_in(MeshVertices, meshVerticess, meshVertices)
        zox_field_i_in(MeshUVs, meshUVss, meshUVs)
        zox_field_i_in(MeshColorRGBs, meshColorRGBss, meshColorRGBs)
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        opengl_upload_shader3D_textured(meshGPULink->value, uvsGPULink->value, colorsGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices->value, meshVertices->length, meshUVs->value, meshColorRGBs->value);
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

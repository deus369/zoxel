void Mesh2DUvsUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    zox_field_out(MeshDirty, meshDirtys, 1)
    zox_field_in(MeshIndicies, meshIndiciess, 2)
    zox_field_in(MeshVertices2D, meshVertices2Ds, 3)
    zox_field_in(MeshUVs, meshUVss, 4)
    zox_field_in(MeshGPULink, meshGPULinks, 5)
    zox_field_in(UvsGPULink, uvsGPULinks, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(MeshDirty, meshDirtys, meshDirty)
        if (!meshDirty->value) continue;
        zox_field_i_in(MeshIndicies, meshIndiciess, meshIndicies)
        if (!meshIndicies->length) continue;
        zox_field_i_in(MeshGPULink, meshGPULinks, meshGPULink)
        if (!meshGPULink->value.x || !meshGPULink->value.y) continue;
        zox_field_i_in(UvsGPULink, uvsGPULinks, uvsGPULink)
        if (!uvsGPULink->value) continue;
        zox_field_i_in(MeshVertices2D, meshVertices2Ds, meshVertices2D)
        zox_field_i_in(MeshUVs, meshUVss, meshUVs)
        opengl_upload_shader2D_textured(meshGPULink->value, uvsGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices2D->value, meshUVs->value, meshVertices2D->length);
        meshDirty->value = 0;
    }
} zox_declare_system(Mesh2DUvsUpdateSystem)

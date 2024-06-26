void MeshUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    zox_field_in(MeshIndicies, meshIndiciess, 2)
    zox_field_in(MeshVertices, meshVerticess, 3)
    zox_field_in(MeshGPULink, meshGPULinks, 4)
    zox_field_in(MaterialGPULink, materialGPULinks, 5)
    zox_field_out(MeshDirty, meshDirtys, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(MeshDirty, meshDirtys, meshDirty)
        if (!meshDirty->value) continue;
        zox_field_i_in(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i_in(MaterialGPULink, materialGPULinks, materialGPULink)
        zox_field_i_in(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_i_in(MeshVertices, meshVerticess, meshVertices)
        opengl_upload_mesh(meshGPULink->value, materialGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices->value, meshVertices->length);
        meshDirty->value = 0;
    }
} zox_declare_system(MeshUpdateSystem)

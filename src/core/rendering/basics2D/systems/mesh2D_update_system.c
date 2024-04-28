void Mesh2DUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    zox_field_out(MeshDirty, meshDirtys, 1)
    zox_field_in(MeshIndicies, meshIndiciess, 2)
    zox_field_in(MeshVertices2D, meshVertices2Ds, 3)
    zox_field_in(MeshGPULink, meshGPULinks, 4)
    zox_field_in(MaterialGPULink, materialGPULinks, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value != 1) continue;
        zox_field_i_in(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i_in(MaterialGPULink, materialGPULinks, materialGPULink)
        zox_field_i_in(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_i_in(MeshVertices2D, meshVertices2Ds, meshVertices2D)
        set_gpu_mesh2D(meshGPULink->value, materialGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices2D->value, meshVertices2D->length);
        meshDirty->value = 0;
    }
} zox_declare_system(Mesh2DUpdateSystem)

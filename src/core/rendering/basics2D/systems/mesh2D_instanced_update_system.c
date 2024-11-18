void Mesh2DInstancedUpdateSystem(ecs_iter_t *it) {
    // if (!ecs_query_changed(NULL, it)) return;
    zox_field_in(MeshDirty, meshDirtys, 1)
    zox_field_in(MeshIndicies, meshIndiciess, 2)
    zox_field_in(MeshVertices2D, meshVerticess, 3)
    zox_field_in(MeshGPULink, meshGPULinks, 4)
    zox_field_in(MaterialInstancedGPULink, materialGPULinks, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value != mesh_state_upload) continue;
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i(MaterialInstancedGPULink, materialGPULinks, materialGPULink)
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_i(MeshVertices2D, meshVerticess, meshVertices)
        set_gpu_mesh2D(meshGPULink->value, materialGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices->value, meshVertices->length);
    }
} zox_declare_system(Mesh2DInstancedUpdateSystem)

void Mesh2DInstancedUpdateSystem(iter *it) {
    // if (!ecs_query_changed(NULL, it)) return;
    zox_sys_begin()
    zox_sys_in(MeshDirty)
    zox_sys_in(MeshIndicies)
    zox_sys_in(MeshVertices2D)
    zox_sys_in(MeshGPULink)
    zox_sys_in(MaterialInstancedGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshDirty, meshDirty)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(MaterialInstancedGPULink, materialGPULink)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshVertices2D, meshVertices)
        if (meshDirty->value != mesh_state_upload) {
            continue;
        }
        set_gpu_mesh2D(meshGPULink->value, materialGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices->value, meshVertices->length);
    }
} zox_declare_system(Mesh2DInstancedUpdateSystem)

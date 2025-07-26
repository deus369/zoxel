void Mesh2DUpdateSystem(ecs_iter_t *it) {
    // if (!ecs_query_changed(NULL, it)) return;
    zox_sys_begin()
    zox_sys_in(MeshDirty)
    zox_sys_in(MeshIndicies)
    zox_sys_in(MeshVertices2D)
    zox_sys_in(MeshGPULink)
    zox_sys_in(MaterialGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshDirty, meshDirty)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(MaterialGPULink, materialGPULink)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshVertices2D, meshVertices2D)
        if (meshDirty->value != mesh_state_upload) {
            continue;
        }
        set_gpu_mesh2D(meshGPULink->value, materialGPULink->value, meshIndicies->value, meshIndicies->length, meshVertices2D->value, meshVertices2D->length);
    }
} zox_declare_system(Mesh2DUpdateSystem)
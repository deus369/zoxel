void Character3LodSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(RenderLodDirty)
    zox_sys_in(RenderLod)
    zox_sys_out(ChunkMeshDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderLodDirty, renderLodDirty)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_o(ChunkMeshDirty, chunkMeshDirty)
        if (renderLodDirty->value == zox_dirty_active) {
            // zox_log_error("character is dirty")
            chunkMeshDirty->value = chunk_dirty_state_trigger;
            // todo: set mesh instance link by renderLod?
            // if instance link
        }
    }
} zox_declare_system(Character3LodSystem)

void Character3LodInstancedSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(RenderLodDirty)
    zox_sys_in(RenderLod)
    zox_sys_in(InstanceLinks)
    zox_sys_out(InstanceLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderLodDirty, renderLodDirty)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(InstanceLinks, instanceLinks)
        zox_sys_o(InstanceLink, instanceLink)
        if (renderLodDirty->value == zox_dirty_active) {
            // zox_log("+ character3_instanced is dirty")
            // use InstanceLinks to set model based on Lod!
            instanceLink->value = instanceLinks->value[renderLod->value];
            // chunkMeshDirty->value = chunk_dirty_state_trigger;
            // todo: set mesh instance link by renderLod?
            // if instance link
        }
    }
} zox_declare_system(Character3LodInstancedSystem)
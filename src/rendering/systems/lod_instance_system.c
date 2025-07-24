void LodInstanceSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RenderLodDirty)
    zox_sys_in(RenderLod)
    zox_sys_in(ModelLink)
    zox_sys_out(InstanceLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderLodDirty, renderLodDirty)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(ModelLink, modelLink)
        zox_sys_o(InstanceLink, instanceLink)
        if (renderLodDirty->value == zox_dirty_active) {
            if (zox_valid(modelLink->value) && zox_has(modelLink->value, ModelLods)) {
                // use InstanceLinks to set model based on Lod!
                zox_geter(modelLink->value, ModelLods, modelLods)
                instanceLink->value = modelLods->value[renderLod->value];
                // zox_sys_e()
                // zox_log("+ %s with model [%s] has set mesh to [%s]", zox_get_name(e), zox_get_name(modelLink->value), zox_get_name(instanceLink->value))
            }
            // some do not
            /*else {
                zox_sys_e()
                zox_log_error("model has no ModelLods [%s]", zox_get_name(e))
            }*/
        }
    }
} zox_declare_system(LodInstanceSystem)
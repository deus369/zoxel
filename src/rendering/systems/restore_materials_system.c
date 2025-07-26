void MaterialRestoreSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ShaderLink)
    zox_sys_out(MaterialGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ShaderLink, shaderLink)
        zox_sys_o(MaterialGPULink, materialGPULink)
#ifdef zox_log_gpu_management
        if (!shaderLink->value) zox_log(" ! no shader_link [%s]\n", zox_get_name(it->entities[i]))
#endif
        if (!shaderLink->value) {
                continue;
        }
        const uint2 shader = zox_get_value(shaderLink->value, ShaderGPULink)
#ifdef zox_log_gpu_management
        zox_log(" > restoring [%s] - shader [%ix%i]\n", zox_get_name(it->entities[i]), shader.x, shader.y)
#endif
        if (!shader.x || !shader.y) {
                continue;
        }
        materialGPULink->value = spawn_gpu_material_program(shader);
    }
} zox_declare_system(MaterialRestoreSystem)

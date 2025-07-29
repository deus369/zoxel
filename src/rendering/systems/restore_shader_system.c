void ShaderRestoreSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(ShaderSourceIndex)
    zox_sys_out(ShaderGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ShaderSourceIndex, shaderSourceIndex)
        zox_sys_o(ShaderGPULink, shaderGPULink)
        if (shaderSourceIndex->value >= zox_max_shaders) {
            continue;
        }
        shaderGPULink->value = zox_gpu_compile_shader(shader_verts[shaderSourceIndex->value], shader_frags[shaderSourceIndex->value]);
#ifdef zox_log_gpu_management
        zox_log(" + restoring [%s] [%i] gpu [%ix%i]\n", zox_get_name(it->entities[i]), shaderSourceIndex->value, shaderGPULink->value.x, shaderGPULink->value.y)
#endif
    }
} zox_declare_system(ShaderRestoreSystem)

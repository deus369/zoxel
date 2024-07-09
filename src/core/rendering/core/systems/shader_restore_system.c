void ShaderRestoreSystem(ecs_iter_t *it) {
    zox_field_in(ShaderSourceIndex, shaderSourceeIndexs, 1)
    zox_field_out(ShaderGPULink, shaderGPULinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ShaderSourceIndex, shaderSourceeIndexs, shaderSourceIndex)
        if (shaderSourceIndex->value >= zox_max_shaders) continue;
        zox_field_o(ShaderGPULink, shaderGPULinks, shaderGPULink)
        shaderGPULink->value = spawn_gpu_shader_inline(shader_verts[shaderSourceIndex->value], shader_frags[shaderSourceIndex->value]);
#ifdef zox_log_gpu_management
        zox_log(" + restoring [%s] [%i] gpu [%ix%i]\n", zox_get_name(it->entities[i]), shaderSourceIndex->value, shaderGPULink->value.x, shaderGPULink->value.y)
#endif
    }
} zox_declare_system(ShaderRestoreSystem)

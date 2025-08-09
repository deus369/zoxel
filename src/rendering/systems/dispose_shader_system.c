void ShaderDisposeSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(ShaderGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ShaderGPULink, shaderGPULink)
#ifdef zox_log_gpu_management
        zox_log(" + disposing [%s] [%ix%i]\n", zox_get_name(it->entities[i]), shaderGPULink->value.x, shaderGPULink->value.x)
#endif
        if (shaderGPULink->value.x) {
            glDeleteShader(shaderGPULink->value.x);
        }
        if (shaderGPULink->value.y) {
            glDeleteShader(shaderGPULink->value.y);
        }
    }
} zoxd_system(ShaderDisposeSystem)
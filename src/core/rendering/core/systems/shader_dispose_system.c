void ShaderDisposeSystem(ecs_iter_t *it) {
    zox_field_in(ShaderGPULink, shaderGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ShaderGPULink, shaderGPULinks, shaderGPULink)
#ifdef zox_log_gpu_management
        zox_log(" + disposing [%s] [%ix%i]\n", zox_get_name(it->entities[i]), shaderGPULink->value.x, shaderGPULink->value.x)
#endif
        if (shaderGPULink->value.x) glDeleteShader(shaderGPULink->value.x);
        if (shaderGPULink->value.y) glDeleteShader(shaderGPULink->value.y);
    }
} zox_declare_system(ShaderDisposeSystem)

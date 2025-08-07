void MaterialDisposeSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(MaterialGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MaterialGPULink, materialGPULink)
#ifdef zox_log_gpu_management
        zox_log(" > disposing [%s] [%i]\n", zox_get_name(it->entities[i]), materialGPULink->value)
#endif
        if (materialGPULink->value) {
            glDeleteProgram(materialGPULink->value);
        }
    }
} zox_declare_system(MaterialDisposeSystem)

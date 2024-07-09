void MaterialDisposeSystem(ecs_iter_t *it) {
    zox_field_in(MaterialGPULink, materialGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MaterialGPULink, materialGPULinks, materialGPULink)
#ifdef zox_log_gpu_management
        zox_log(" > disposing [%s] [%i]\n", zox_get_name(it->entities[i]), materialGPULink->value)
#endif
        if (materialGPULink->value) glDeleteProgram(materialGPULink->value);
    }
} zox_declare_system(MaterialDisposeSystem)

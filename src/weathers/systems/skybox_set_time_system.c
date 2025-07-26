void SkyboxSetTimeSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(MaterialGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MaterialGPULink, materialGPULink)
        const uint material = materialGPULink->value;
        if (!material) {
            continue;
        }
        zox_gpu_material(material);
        const uint attribute_time = glGetUniformLocation(material, "time");
        zox_gpu_float(attribute_time, (float) zox_current_time);
        zox_gpu_material(0);
    }
} zox_declare_system(SkyboxSetTimeSystem)

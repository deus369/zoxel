void SkyboxSetTimeSystem(ecs_iter_t *it) {
    zox_field_in(MaterialGPULink, materialGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MaterialGPULink, materialGPULinks, materialGPULink)
        const GLuint material = materialGPULink->value;
        if (!material) {
            return;
        }
        opengl_set_material(material);
        const GLuint attribute_time = glGetUniformLocation(material, "time");
        opengl_set_float(attribute_time, (float) zox_current_time);
        opengl_set_material(0);
    }
} zox_declare_system(SkyboxSetTimeSystem)

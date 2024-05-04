void MaterialRestoreSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ShaderLink, shaderLinks, 1)
    zox_field_out(MaterialGPULink, materialGPULinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ShaderLink, shaderLinks, shaderLink)
#ifdef zox_log_gpu_management
        if (!shaderLink->value) zox_log(" ! no shader_link [%s]\n", zox_get_name(it->entities[i]))
#endif
        if (!shaderLink->value) continue;
        zox_field_i_out(MaterialGPULink, materialGPULinks, materialGPULink)
        const GLuint2 shader = zox_get_value(shaderLink->value, ShaderGPULink)
#ifdef zox_log_gpu_management
        zox_log(" > restoring [%s] - shader [%ix%i]\n", zox_get_name(it->entities[i]), shader.x, shader.y)
#endif
        if (!shader.x || !shader.y) continue;
        materialGPULink->value = spawn_gpu_material_program(shader);
    }
} zox_declare_system(MaterialRestoreSystem)

void SkyboxRestoreSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(MaterialGPULink, materialGPULinks, 1)
    zox_field_in(ColorRGB, colors, 2)
    zox_field_in(SecondaryColorRGB, secondaryColors, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(MaterialGPULink, materialGPULinks, materialGPULink)
        zox_field_i_in(ColorRGB, colors, color)
        zox_field_i_in(SecondaryColorRGB, secondaryColors, secondaryColor)
        const GLuint material = materialGPULink->value;
        if (!material) return;
        opengl_set_material(material);
        const GLuint color_location = glGetUniformLocation(material, "sky_top_color");
        const GLuint secondary_color_location = glGetUniformLocation(material, "sky_bottom_color");
        opengl_set_float3(color_location, color_rgb_to_float3(color->value));
        opengl_set_float3(secondary_color_location, color_rgb_to_float3(secondaryColor->value));
        opengl_set_material(0);
#ifdef zox_log_gpu_management
        zox_log("restoring skybox [%s]\n", zox_get_name(it->entities[i]))
#endif
    }
} zox_declare_system(SkyboxRestoreSystem)

void SkyboxRestoreSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(MaterialGPULink)
    zox_sys_in(ColorRGB)
    zox_sys_in(SecondaryColorRGB)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MaterialGPULink, materialGPULink)
        zox_sys_i(ColorRGB, color)
        zox_sys_i(SecondaryColorRGB, secondaryColor)
        const uint material = materialGPULink->value;
        if (!material) {
            zox_log(" ! [%i] skybox material invalid.\n", i)
            continue;
        }
        zox_gpu_material(material);
        const uint color_location = glGetUniformLocation(material, "sky_top_color");
        const uint secondary_color_location = glGetUniformLocation(material, "sky_bottom_color");
        zox_gpu_float3(color_location, color_rgb_to_float3(color->value));
        zox_gpu_float3(secondary_color_location, color_rgb_to_float3(secondaryColor->value));
        zox_gpu_material(0);
        if (is_log_gpu_restore) {
            zox_sys_world()
            zox_sys_e()
            zox_log("+ restoring skybox [%s]\n", zox_get_name(e))
            zox_log(" - color [%ix%ix%i] secondary [%ix%ix%i]", color->value.r, color->value.g, color->value.b, secondaryColor->value.r, secondaryColor->value.g, secondaryColor->value.b)
        }
    }
} zox_declare_system(SkyboxRestoreSystem)

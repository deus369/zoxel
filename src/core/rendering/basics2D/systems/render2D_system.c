void RenderMaterial2DSystem(ecs_iter_t *it) {
    zox_field_in(Position2D, position2Ds, 1)
    zox_field_in(Rotation2D, rotation2Ds, 2)
    zox_field_in(Scale1D, scale1Ds, 3)
    zox_field_in(Brightness, brightnesss, 4)
    zox_field_in(MaterialGPULink, materialGPULinks, 5)
    zox_field_in(TextureGPULink, textureGPULinks, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Position2D, position2Ds, position2D)
        zox_field_i_in(Rotation2D, rotation2Ds, rotation2D)
        zox_field_i_in(Scale1D, scale1Ds, scale1D)
        zox_field_i_in(Brightness, brightnesss, brightness)
        zox_field_i_in(MaterialGPULink, materialGPULinks, materialGPULink)
        zox_field_i_in(TextureGPULink, textureGPULinks, textureGPULink)
        render_entity_material2D(render_camera_matrix, materialGPULink->value, textureGPULink->value, position2D->value, rotation2D->value, scale1D->value, brightness->value);
    }
} zox_declare_system(RenderMaterial2DSystem)

void TextureRestoreSystem(ecs_iter_t *it) {
    zox_field_out(TextureGPULink, textureGPULinks, 1)
    zox_field_out(TextureDirty, textureDirtys, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TextureGPULink, textureGPULinks, textureGPULink)
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        textureGPULink->value = spawn_gpu_texture_buffer();
        textureDirty->value = 1;
    }
} zox_declare_system(TextureRestoreSystem)

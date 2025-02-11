void TextureRestoreSystem(ecs_iter_t *it) {
    zox_field_out(TextureGPULink, textureGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TextureGPULink, textureGPULinks, textureGPULink)
        textureGPULink->value = spawn_gpu_texture_buffer();
    }
} zox_declare_system(TextureRestoreSystem)

void TextureDirtyRestoreSystem(ecs_iter_t *it) {
    zox_field_out(TextureDirty, textureDirtys, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        textureDirty->value = 1;
    }
} zox_declare_system(TextureDirtyRestoreSystem)

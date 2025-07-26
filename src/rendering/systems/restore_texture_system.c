void TextureRestoreSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_out(TextureGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(TextureGPULink, textureGPULink)
        textureGPULink->value = spawn_gpu_texture_buffer();
    }
} zox_declare_system(TextureRestoreSystem)

void TextureDirtyRestoreSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_out(TextureDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(TextureDirty, textureDirty)
        textureDirty->value = 1;
    }
} zox_declare_system(TextureDirtyRestoreSystem)

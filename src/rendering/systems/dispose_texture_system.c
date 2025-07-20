void TextureGPUDisposeSystem(ecs_iter_t *it) {
    zox_field_in(TextureGPULink, textureGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        if (textureGPULink->value != 0) {
            glDeleteTextures(1, &textureGPULink->value);
        }
    }
} zox_declare_system(TextureGPUDisposeSystem)

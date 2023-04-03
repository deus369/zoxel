//! Generate random noise texture.
/**
 * Once main thread is fixed, update to gpu in this system.
 * \todo update to gpu here?
*/
void TextureUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) {
        return;
    }
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 1);
    const Texture *textures = ecs_field(it, Texture, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 4);
    // printf("TextureUpdateSystem [%i] \n", it->count);
    for (int i = 0; i < it->count; i++) {
        TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value == 1) {
            textureDirty->value = 0;
            const Texture *texture = &textures[i];
            const TextureSize *textureSize = &textureSizes[i];
            const TextureGPULink *textureGPULink = &textureGPULinks[i];
            // printf("Uploaded Texture to GPU: %lu -TextureID [%i] \n", (long int) it->entities[i], textureGPULink->value);
            glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y,
                0, GL_RGBA, GL_UNSIGNED_BYTE, texture->value);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}
zoxel_declare_system(TextureUpdateSystem)
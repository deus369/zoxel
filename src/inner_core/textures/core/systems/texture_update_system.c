void TextureUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) {
        return;
    }
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 1);
    const TextureData *textures = ecs_field(it, TextureData, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 4);
    for (int i = 0; i < it->count; i++) {
        TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value == 1) {
            const TextureData *textureData = &textures[i];
            const TextureSize *textureSize = &textureSizes[i];
            const TextureGPULink *textureGPULink = &textureGPULinks[i];
            textureDirty->value = 0;
            if (textureGPULink->value == 0) {
                continue;
            }
            glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData->value);
            glBindTexture(GL_TEXTURE_2D, 0);
            // zoxel_log(" + uploaded entity [%lu] textureData [%i] to gpu\n", it->entities[i], textureGPULink->value);
        }
    }
}
zox_declare_system(TextureUpdateSystem)
void TextureUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 1);
    const TextureData *textures = ecs_field(it, TextureData, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 4);
    for (int i = 0; i < it->count; i++) {
        TextureDirty *textureDirty = &textureDirtys[i];
        if (!textureDirty->value) continue;
        const TextureData *textureData = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        if (textureGPULink->value != 0 && textureData->value) {
            if (!headless) {
                // const int texture_type = GL_NEAREST; // GL_NEAREST | GL_LINEAR
                glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData->value);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_type);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_type);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            textureDirty->value = 0;
            // zox_log("   > entity texture uploaded [%lu] gpu > [%i]\n", it->entities[i], textureGPULink->value);
        }
    }
} zox_declare_system(TextureUpdateSystem)

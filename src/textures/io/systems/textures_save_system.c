const char *outputTextureName = resources_folder_name"textures/tester.png"; // testing

void TextureSaveSystem(ecs_iter_t *it) {
    zox_skip_if_unchanged(1)
    // if (!ecs_query_changed(NULL, it)) return;
    zox_field_in(TextureDirty, textureDirtys, 1)
    zox_field_in(TextureData, textures, 2)
    zox_field_in(TextureSize, textureSizes, 3)
    for (int i = 0; i < it->count; i++) {
        const TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value != 1) {
            continue;
        }
        const TextureData *textureData = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        save_texture_as_png(textureData->value, textureSize->value, outputTextureName);
        zox_log(" > saved texture: %lu as [%s]\n", (long int) it->entities[i], outputTextureName)
    }
} zox_declare_system(TextureSaveSystem)

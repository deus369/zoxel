const char *outputTextureName = resources_folder_name"textures/tester.png"; // testing

void TextureSaveSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) {
        return;
    }
    const TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 1);
    const TextureData *textures = ecs_field(it, TextureData, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    for (int i = 0; i < it->count; i++) {
        const TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value != 1) {
            continue;
        }
        const TextureData *textureData = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        save_texture_png(textureData, textureSize, outputTextureName);
        zoxel_log("Saved TextureData: %lu \n", (long int) it->entities[i]);
    }
}
zoxel_declare_system(TextureSaveSystem)
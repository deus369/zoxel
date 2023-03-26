// For testing for now
const char *outputTextureName = resources_folder_name"textures/tester.png";

//! Generate random noise texture.
/**
 * \todo update to gpu here?
*/
void TextureSaveSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) {
        return;
    }
    const TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 1);
    const Texture *textures = ecs_field(it, Texture, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    for (int i = 0; i < it->count; i++) {
        const TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value != 1) {
            continue;
        }
        const Texture *texture = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        save_texture_png(texture, textureSize, outputTextureName);
        zoxel_log("Saved Texture: %lu \n", (long int) it->entities[i]);
    }
}
zoxel_declare_system(TextureSaveSystem)
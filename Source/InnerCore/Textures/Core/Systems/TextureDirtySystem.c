// For testing for now
const char *outputTextureName = "Resources/Textures/Test.png";

//! Generate random noise texture.
/**
 * \todo update to gpu here?
*/
void TextureDirtySystem(ecs_iter_t *it)
{
    /*if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    const EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 1);
    const Texture *textures = ecs_field(it, Texture, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    for (int i = 0; i < it->count; i++)
    {
        const EntityDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value != 1)
        {
            continue;
        }
        const Texture *texture = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        SaveAsPNG(texture, textureSize, outputTextureName);
        // printf("Saved Texture: %lu \n", (long int) it->entities[i]);
    }*/
}
ECS_SYSTEM_DECLARE(TextureDirtySystem);
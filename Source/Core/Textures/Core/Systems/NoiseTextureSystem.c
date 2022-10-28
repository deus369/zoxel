//! Generate random noise texture.
void NoiseTextureSystem(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    const int2 redRange = { 55, 188 };
    const int2 greenRange = { 15, 88 };
    const int2 blueRange = { 15, 88 };
    // printf("Noise Texture System, Component Changed!!\n");
    EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 2);
    Texture *textures = ecs_field(it, Texture, 3);
    const GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 4);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 5);
    int index;
    for (int i = 0; i < it->count; i++)
    {
        EntityDirty *entityDirty = &entityDirtys[i];
        const GenerateTexture *generateTexture = &generateTextures[i];
        //! Only rebuild if GenerateTexture is set to true and EntityDirty is false.
        if (generateTexture->value == 0 || entityDirty->value != 0)
        {
            continue;
        }
        // generateTexture->value = 0;
        entityDirty->value = 1;
        // printf("Noise Texture Generated! %lu \n", (long int) it->entities[i]);
        Texture *texture = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        initialize_memory_component(texture, color, textureSize->value.x * textureSize->value.y);
        for (int j = 0; j < textureSize->value.x; j++)
        {
            for (int k = 0; k < textureSize->value.y; k++)
            {
                index = j + k * textureSize->value.x;
                texture->value[index].r = redRange.x + rand() % (redRange.y - redRange.x);
                texture->value[index].g = greenRange.x + rand() % (greenRange.y - greenRange.x);
                texture->value[index].b = blueRange.x + rand() % (blueRange.y - blueRange.x);
                texture->value[index].a = rand() % 256;
                // debug sides of texture, starts at top left
                if (j == 0)
                {
                    texture->value[index].r = 255;
                }
                else if (k == 0)
                {
                    texture->value[index].g = 255;
                }
                else if (j == textureSize->value.x - 1)
                {
                    texture->value[index].b = 255;
                }
                else if (k == textureSize->value.y - 1)
                {
                    texture->value[index].r = 255;
                    texture->value[index].g = 255;
                }
                // printf("texture value: %i\n", texture->value[index].r);
            }
        }
    }
}
ECS_SYSTEM_DECLARE(NoiseTextureSystem);
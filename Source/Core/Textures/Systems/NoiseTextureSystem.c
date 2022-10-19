//! Generate random noise texture.
void NoiseTextureSystem(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    // printf("Noise Texture System, Component Changed!!\n");
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 2);
    EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 3);
    Texture *textures = ecs_field(it, Texture, 4);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 5);
    int index;
    for (int i = 0; i < it->count; i++)
    {
        GenerateTexture *generateTexture = &generateTextures[i];
        EntityDirty *entityDirty = &entityDirtys[i];
        if (generateTexture->value == 1 && entityDirty->value != 0)
        {
            continue;
        }
        generateTexture->value = 0;
        entityDirty->value = 1;
        // printf("Noise was generated! %lu \n", (long int) it->entities[i]);
        Texture *texture = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        texture->value = malloc(textureSize->value.x * textureSize->value.y * 4);
        for (int j = 0; j < textureSize->value.x; j++)
        {
            for (int k = 0; k < textureSize->value.y; k++)
            {
                index = j + k * textureSize->value.x;
                texture->value[index].r = rand() % 256;
                texture->value[index].g = rand() % 256;
                texture->value[index].b = rand() % 256;
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
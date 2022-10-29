int abs_integer(int value)
{
    if (value < 0)
    {
        return -value;
    }
    else
    {
        return value;
    }
}

//! Our function that creates a texture.
void GenerateNoise(Texture* texture, const TextureSize *textureSize)
{
    const int2 redRange = { 15, 244 };
    const int2 greenRange = { 15, 122 };
    const int2 blueRange = { 15, 122 };
    const int2 alphaRange = { 144, 256 };
    for (int j = 0; j < textureSize->value.x; j++)
    {
        for (int k = 0; k < textureSize->value.y; k++)
        {
            int index = j + k * textureSize->value.x;
            int distanceToMidX = abs_integer(textureSize->value.x / 2 - j);
            int distanceToMidY = abs_integer(textureSize->value.y / 2 - k);
            if (distanceToMidX + distanceToMidY >= textureSize->value.x / 2)
            {
                texture->value[index].r = 0;
                texture->value[index].g = 0;
                texture->value[index].b = 0;
                texture->value[index].a = 0;
                continue;
            }
            texture->value[index].r = redRange.x + rand() % (redRange.y - redRange.x);
            texture->value[index].g = greenRange.x + rand() % (greenRange.y - greenRange.x);
            texture->value[index].b = blueRange.x + rand() % (blueRange.y - blueRange.x);
            texture->value[index].a = alphaRange.x + rand() % (alphaRange.y - alphaRange.x);
            // texture->value[index].a = rand() % 256;
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

//! Generate random noise texture.
void NoiseTextureSystem(ecs_iter_t *it)
{
    //! This breaks the updates. \todo Fix this. Find out why it doesn't work properly.
    /*ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery)
    {
        printf("[404; changeQuery is void]\n");
        return;
    }
    if (!ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    ecs_iter_t changeIterator = ecs_query_iter(it->world, changeQuery);
    while (ecs_query_next(&changeIterator));*/
    // printf("NoiseTextureSystem: [GenerateTexture Changed]\n");
    EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 2);
    Texture *textures = ecs_field(it, Texture, 3);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 4);
    const GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 5);
    for (int i = 0; i < it->count; i++)
    {
        const GenerateTexture *generateTexture = &generateTextures[i];
        //! Only rebuild if GenerateTexture is set to true and EntityDirty is false.
        if (generateTexture->value == 0)
        {
            continue;
        }
        EntityDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value != 0)
        {
            continue;
        }
        entityDirty->value = 1;
        // printf("Noise Texture Generated: [%lu] \n", (long int) it->entities[i]);
        Texture *texture = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        re_initialize_memory_component(texture, color, textureSize->value.x * textureSize->value.y);
        GenerateNoise(texture, textureSize);
    }
}
ECS_SYSTEM_DECLARE(NoiseTextureSystem);
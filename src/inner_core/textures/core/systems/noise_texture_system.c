//! Our function that creates a texture.
void GenerateNoise(Texture* texture, const TextureSize *textureSize, unsigned char is_dirt)
{
    int2 redRange = { 15, 244 };
    int2 greenRange = { 15, 122 };
    int2 blueRange = { 15, 122 };
    int2 alphaRange = { 144, 256 };
    if (is_dirt)
    {
        redRange = (int2) { 53, 93 };  // 73
        greenRange = (int2) { 37, 57 };  // 47
        blueRange = (int2) { 7, 27 };  // 17
        alphaRange = (int2) { 255, 256 };
    }
    for (int j = 0; j < textureSize->value.x; j++)
    {
        for (int k = 0; k < textureSize->value.y; k++)
        {
            int index = j + k * textureSize->value.x;
            if (!is_dirt)
            {
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
            }
            texture->value[index].r = redRange.x + rand() % (redRange.y - redRange.x);
            texture->value[index].g = greenRange.x + rand() % (greenRange.y - greenRange.x);
            texture->value[index].b = blueRange.x + rand() % (blueRange.y - blueRange.x);
            texture->value[index].a = alphaRange.x + rand() % (alphaRange.y - alphaRange.x);
            // texture->value[index].a = rand() % 256;
            // debug sides of texture, starts at top left
            if (!is_dirt)
            {
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
            }
            // outline voxel textures
            else if (is_texture_outlines)
            {
                if (j == 0 || k == 0 || j == textureSize->value.x - 1 || k == textureSize->value.y - 1)
                {
                    texture->value[index].r /= 2;
                    texture->value[index].g /= 2;
                    texture->value[index].b /= 2;
                }
            }
            // printf("texture value: %i\n", texture->value[index].r);
        }
    }
}

void NoiseTextureSystem(ecs_iter_t *it)
{
    //! This breaks the updates. \todo Fix this. Find out why it doesn't work properly.
    //! This doesn't work because the table writes all changes in the first iteration which is for one entity.
    //!     Possible fix: Make a second system that writes changes at the end of the loop
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    // ecs_iter_t changeIterator = ecs_query_iter(it->world, changeQuery);
    // while (ecs_query_next(&changeIterator));
    // printf("NoiseTextureSystem: [GenerateTexture Changed]\n");
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 2);
    Texture *textures = ecs_field(it, Texture, 3);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 4);
    const GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 5);
    for (int i = 0; i < it->count; i++)
    {
        const GenerateTexture *generateTexture = &generateTextures[i];
        //! Only rebuild if GenerateTexture is set to 1 and EntityDirty is false.
        if (generateTexture->value == 0)
        {
            continue;
        }
        TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value != 0)
        {
            continue;
        }
        textureDirty->value = 1;
        Texture *texture = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        int newLength = textureSize->value.x * textureSize->value.y;
        re_initialize_memory_component(texture, color, newLength);
        unsigned char is_dirt = ecs_has(it->world, it->entities[i], DirtTexture);
        GenerateNoise(texture, textureSize, is_dirt);
        // printf("Noise Texture Generated: [%lu] \n", (long int) it->entities[i]);
    }
}
zoxel_declare_system(NoiseTextureSystem)
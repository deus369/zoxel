// when font is dirty, update it
// generate font texture based on byte2 points

//! Our function that creates a texture.
void generate_font_texture(Texture* texture, const TextureSize *textureSize)
{
    // use FontData byte2 data.
    const int frame_thickness = textureSize->value.x / 4;
    const int2 redRange = { 15, 244 };
    const int2 greenRange = { 15, 122 };
    const int2 blueRange = { 15, 122 };
    const int2 alphaRange = { 144, 256 };
    const int2 alphaRange2 = { 222, 256 };
    color base = { 
        redRange.x + rand() % (redRange.y - redRange.x),
        greenRange.x + rand() % (greenRange.y - greenRange.x),
        blueRange.x + rand() % (blueRange.y - blueRange.x),
        alphaRange.x + rand() % (alphaRange.y - alphaRange.x)
    };
    color darker = { 
        redRange.x + rand() % (redRange.y - redRange.x),
        greenRange.x + rand() % (greenRange.y - greenRange.x),
        blueRange.x + rand() % (blueRange.y - blueRange.x),
        alphaRange2.x + rand() % (alphaRange2.y - alphaRange2.x)
    };
    int index = 0;
    for (int k = 0; k < textureSize->value.y; k++)
    {
        for (int j = 0; j < textureSize->value.x; j++)
        {
            if (j <= frame_thickness || k <= frame_thickness || j >= textureSize->value.x - 1 - frame_thickness || k >= textureSize->value.y - 1 - frame_thickness)
            {
                texture->value[index] = base;
            }
            else
            {
                texture->value[index] = darker;
            }
            index++;
        }
    }
}

void FontTextureSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
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
        Texture *texture = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        int newLength = textureSize->value.x * textureSize->value.y;
        re_initialize_memory_component(texture, color, newLength);
        generate_font_texture(texture, textureSize);
    }
}
ECS_SYSTEM_DECLARE(FontTextureSystem);
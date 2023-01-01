unsigned char check_texture(Texture* texture, const TextureSize *textureSize, int2 pixel_position,
    color find_color, int distance)
{
    if (!int2_in_bounds(pixel_position, textureSize->value))
    {
        return 0;
    }
    if (color_equal(find_color, texture->value[int2_array_index(pixel_position, textureSize->value)]))
    {
        return 1;
    }
    if (distance >= 0)
    {
        distance--;
        if (check_texture(texture, textureSize, int2_down(pixel_position), find_color, distance))
        {
            return 1;
        }
        if (check_texture(texture, textureSize, int2_up(pixel_position), find_color, distance))
        {
            return 1;
        }
        if (check_texture(texture, textureSize, int2_left(pixel_position), find_color, distance))
        {
            return 1;
        }
        if (check_texture(texture, textureSize, int2_right(pixel_position), find_color, distance))
        {
            return 1;
        }
    }
    return 0;
}

//! Our function that creates a texture.
void generate_frame_texture(Texture* texture, const TextureSize *textureSize)
{
    const int empty_buffer = 6;
    const int frame_thickness = 2;
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
    color empty = { 0, 0, 0, 0 };
    int index = 0;
    int2 pixel_position = { 0, 0 };
    for (pixel_position.y = 0; pixel_position.y < textureSize->value.y; pixel_position.y++)
    {
        for (pixel_position.x = 0; pixel_position.x < textureSize->value.x; pixel_position.x++)
        {
            // corner
            int distance_to_corner_a = pixel_position.x + pixel_position.y;
            int distance_to_corner_b = (textureSize->value.x - 1 - pixel_position.x) + pixel_position.y;
            int distance_to_corner_c = (textureSize->value.x - 1 - pixel_position.x) + (textureSize->value.y - 1 - pixel_position.y);
            int distance_to_corner_d = pixel_position.x + (textureSize->value.y - 1 - pixel_position.y);
            if (distance_to_corner_a <= empty_buffer || distance_to_corner_b <= empty_buffer
                || distance_to_corner_c <= empty_buffer || distance_to_corner_d <= empty_buffer)
            {
                texture->value[index] = empty;
            }
            else
            {
                texture->value[index] = base;
            }
            index++;
        }
    }
    // outline of frame
    index = 0;
    for (pixel_position.y = 0; pixel_position.y < textureSize->value.y; pixel_position.y++)
    {
        for (pixel_position.x = 0; pixel_position.x < textureSize->value.x; pixel_position.x++)
        {
            if (!color_equal(texture->value[index], base))
            {
                index++;
                continue;
            }
            if (pixel_position.x <= frame_thickness ||
                pixel_position.y <= frame_thickness ||
                pixel_position.x >= textureSize->value.x - 1 - frame_thickness ||
                pixel_position.y >= textureSize->value.y - 1 - frame_thickness)
            {
                texture->value[index] = darker;
            }
            else if (check_texture(texture, textureSize, pixel_position, empty, frame_thickness))
            {
                texture->value[index] = darker;
            }
            index++;
        }
    }
}
                /* || color_equal(texture->value[int2_array_index(int2_down(pixel_position), textureSize->value)], empty) ||
                color_equal(texture->value[int2_array_index(int2_up(pixel_position), textureSize->value)], empty) ||
                color_equal(texture->value[int2_array_index(int2_left(pixel_position), textureSize->value)], empty) ||
                color_equal(texture->value[int2_array_index(int2_right(pixel_position), textureSize->value)], empty)*/
                

            //if (j <= empty_buffer || j >= textureSize->value.x - 1 - empty_buffer
            //    || k <= empty_buffer || k >= textureSize->value.y - 1 - empty_buffer)
            /*else if (j <= frame_thickness || k <= frame_thickness || j >= textureSize->value.x - 1 - frame_thickness || k >= textureSize->value.y - 1 - frame_thickness)
            {
                texture->value[index] = darker;
            }*/

void FrameTextureSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
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
        generate_frame_texture(texture, textureSize);
    }
}
ECS_SYSTEM_DECLARE(FrameTextureSystem);
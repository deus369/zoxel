const char *outputTextureName = "Resources/Textures/Test.png";

//! Save PNG to file using SDL
/**
 * https://wiki.libsdl.org/SDL_CreateTexture
 * https://wiki.libsdl.org/SDL_UpdateTexture
*/
void SaveAsPNG(const Texture *texture, const TextureSize *textureSize)
{
    // https://wiki.libsdl.org/SDL_PixelFormatEnum
    // int req_format = STBI_rgb_alpha;
    int rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    int shift = 0; // (req_format == STBI_rgb) ? 8 : 0;
    rmask = 0xff000000 >> shift;
    gmask = 0x00ff0000 >> shift;
    bmask = 0x0000ff00 >> shift;
    amask = 0x000000ff >> shift;
    #else // little endian, like x86
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0; // (req_format == STBI_rgb) ? 0 : 0xff000000;
    #endif
    int depth = 32;
    int pitch = textureSize->value.x * 4;
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)texture->value, textureSize->value.x, textureSize->value.y,
        depth, pitch, rmask, gmask, bmask, amask);
    if(IMG_SavePNG(surface, outputTextureName) != 0)
    {
        // Error saving bitmap
        printf("SDL_SaveBMP failed: %s\n", SDL_GetError());
    }
    // when you don't need the surface anymore, free it..
    SDL_FreeSurface(surface);
}

//! Generate random noise texture.
void TextureDirtySystem(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    // printf("TextureDirtySystem!\n");
    double deltaTime = (double) it->delta_time;
    EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 1);
    const Texture *textures = ecs_field(it, Texture, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    for (int i = 0; i < it->count; i++)
    {
        EntityDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value != 1)
        {
            continue;
        }
        entityDirty->value = 0; // set to 0 in a post update system?
        const Texture *texture = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        SaveAsPNG(texture, textureSize);
        // printf("Texture was updated! %lu \n", (long int) it->entities[i]);
        // update to gpu here?
    }
}
ECS_SYSTEM_DECLARE(TextureDirtySystem);


    /*
    extern SDL_Renderer *renderer;
    SDL_Texture* sdlTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STATIC,
        textureSize->value.x,
        textureSize->value.y);*/

    // SDL_Rect sdlRect = { 0, 0, textureSize->value.x, textureSize->value.y };
    // SDL_UpdateTexture(sdlTexture, &sdlRect, &texture->value, textureSize->value.x * 4);
    // SDL_Surface* surface = SDL_LoadBMP("image.bmp");
#ifdef zoxel_using_sdl_images

SDL_Surface* load_png_as_surface(const char *filepath) {
    return (SDL_Surface*) IMG_Load(filepath);
}

// Assuming TextureData and TextureSize are defined as they are in your save function
void load_texture_from_png(const char *filepath, TextureData *textureData, TextureSize *textureSize) {
    SDL_Surface* loadedSurface = IMG_Load(filepath);
    if (!loadedSurface) {
        // Error loading PNG
        zox_log(" ! failed with [IMG_Load]: %s\n", SDL_GetError())
        return;
    }
    textureSize->value.x = loadedSurface->w;
    textureSize->value.y = loadedSurface->h;
    // Here, I assume your TextureData structure is designed to store raw pixel data.
    // You might need to adjust this part depending on the exact structure of TextureData
    int byte_length = textureSize->value.x * textureSize->value.y * sizeof(color);
    resize_memory_component(TextureData, textureData, color, byte_length)
    // textureData->value = malloc(loadedSurface->w * loadedSurface->h * 4); // Assuming 4 bytes per pixel (RGBA)
    memcpy(textureData->value, loadedSurface->pixels, byte_length); //  loadedSurface->w * loadedSurface->h * 4);
    SDL_FreeSurface(loadedSurface);
}

void save_texture_as_png(const TextureData *textureData, const TextureSize *textureSize, const char *filepath) {
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
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*) textureData->value, textureSize->value.x, textureSize->value.y, depth, pitch, rmask, gmask, bmask, amask);
    if(IMG_SavePNG(surface, filepath) != 0) {
        // Error saving bitmap
        zox_log(" ! failed with [IMG_SavePNG]: %s\n", SDL_GetError())
    }
    SDL_FreeSurface(surface);
}

#else

SDL_Surface* load_png_as_surface(const char *filepath) { return NULL; }

void save_texture_as_png(const TextureData *textureData, const TextureSize *textureSize, const char *outputTextureName) { }

#endif

void load_app_icon(SDL_Window* window, const char *icon_filepath) {
    SDL_Surface *surface = load_png_as_surface(icon_filepath); // IMG_Load(icon_filepath); // IMG_Load(buffer);
    if (surface != NULL) {
        SDL_SetWindowIcon(window, surface); // The icon is attached to the window pointer
        SDL_FreeSurface(surface);
    }
}

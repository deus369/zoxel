#ifdef zox_using_sdl_images

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
    int colors_length = textureSize->value.x * textureSize->value.y;
    int byte_length = colors_length * sizeof(color);
    resize_memory_component(TextureData, textureData, color, colors_length)
    // textureData->value = malloc(loadedSurface->w * loadedSurface->h * 4); // Assuming 4 bytes per pixel (RGBA)
    memcpy(textureData->value, loadedSurface->pixels, byte_length); //  loadedSurface->w * loadedSurface->h * 4);
    SDL_FreeSurface(loadedSurface);
}

void save_texture_as_png(const color *data, const int2 size, const char *filepath) {
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
    int pitch = size.x * 4;
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*) data, size.x, size.y, depth, pitch, rmask, gmask, bmask, amask);
    if(IMG_SavePNG(surface, filepath) != 0) {
        // Error saving bitmap
        zox_log(" ! failed with [IMG_SavePNG]: %s\n", SDL_GetError())
    }
    SDL_FreeSurface(surface);
}

#else

SDL_Surface* load_png_as_surface(const char *filepath) { return NULL; }

void load_texture_from_png(const char *filepath, TextureData *textureData, TextureSize *textureSize) { }

void save_texture_as_png(const TextureData *textureData, const TextureSize *textureSize, const char *outputTextureName) { }

#endif

void load_app_icon(SDL_Window* window, const char *icon_path) {
#ifndef zox_disable_io
    SDL_Surface *surface = load_png_as_surface(icon_path);
    if (surface == NULL) {
        zox_log(" ! failed to load app icon [%s]\n", icon_path);
    } else  {
        SDL_SetWindowIcon(window, surface);
        SDL_FreeSurface(surface);
    }
#endif
}

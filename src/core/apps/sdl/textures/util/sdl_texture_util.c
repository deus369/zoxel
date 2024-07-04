#ifdef zox_lib_sdl_images

SDL_Surface* load_png_as_surface(const char *filepath) {
#ifndef zox_lib_sdl_images
    return NULL;
#else
    return (SDL_Surface*) IMG_Load(filepath);
#endif
}

// Assuming TextureData and TextureSize are defined as they are in your save function
color* load_texture_from_png(const char *filepath, int2 *size, int *length) {
    SDL_Surface* loadedSurface = IMG_Load(filepath);
    if (!loadedSurface) {
        zox_log(" ! failed with [IMG_Load]: %s\n", SDL_GetError())
        return NULL;
    }
    size->x = loadedSurface->w;
    size->y = loadedSurface->h;
    // Here, I assume your TextureData structure is designed to store raw pixel data.
    // You might need to adjust this part depending on the exact structure of TextureData
    int colors_length = size->x * size->y;
    *length = colors_length;
    int byte_length = colors_length * sizeof(color);
    color* data = (color*) malloc(byte_length);
    // resize_memory_component(TextureData, data, color, colors_length)
    // textureData->value = malloc(loadedSurface->w * loadedSurface->h * 4); // Assuming 4 bytes per pixel (RGBA)

    // Flip the image vertically
    // remember: sdl considers top left origin, while opengl is bottom left
    int pitch = loadedSurface->pitch;
    unsigned char* pixels = (unsigned char*)loadedSurface->pixels;
    for (int y = 0; y < size->y; ++y) {
        memcpy(data + (size->y - 1 - y) * size->x, pixels + y * pitch, size->x * sizeof(color));
    }

    // memcpy(data, loadedSurface->pixels, byte_length); //  loadedSurface->w * loadedSurface->h * 4);
    SDL_FreeSurface(loadedSurface);
    return data;
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

color* load_texture_from_png(const char *filepath, int2 *size, int *length) { return NULL; }

void save_texture_as_png(const color *data, const int2 size, const char *filepath) { }

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

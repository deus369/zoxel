#ifdef zox_lib_sdl_images

SDL_Surface* load_png_as_surface(const char *filepath) {
#ifndef zox_lib_sdl_images
    return NULL;
#else
    return (SDL_Surface*) IMG_Load(filepath);
#endif
}

// Assuming TextureData and TextureSize are defined as they are in your save function
color* load_texture_from_png(const char *filepath, int2 *size) {
    SDL_Surface* surface = IMG_Load(filepath);
    if (!surface) {
        zox_log(" ! failed with [IMG_Load]: %s\n", SDL_GetError())
        return NULL;
    }
    const int pitch = surface->pitch;
    size->x = surface->w;
    size->y = surface->h;
    const int colors_length = size->x * size->y;
    const int byte_length = colors_length * sizeof(color);
    // Flip the image vertically
    // remember: sdl considers top left origin, while opengl is bottom left
    unsigned char* pixels = (unsigned char*) surface->pixels;
    color* data = (color*) malloc(byte_length);
    for (int y = 0; y < size->y; ++y) memcpy(data + (size->y - 1 - y) * size->x, pixels + y * pitch, size->x * sizeof(color));
    SDL_FreeSurface(surface);
    return data;
}

// resize_memory_component(TextureData, data, color, colors_length)
// textureData->value = malloc(loadedSurface->w * loadedSurface->h * 4); // Assuming 4 bytes per pixel (RGBA)
// memcpy(data, surface->pixels, byte_length); //  surface->w * surface->h * 4);

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

color* load_texture_from_png(const char *filepath, int2 *size) {
    zox_log(" ! sdl_image is disabled\n")
    return NULL;
}

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

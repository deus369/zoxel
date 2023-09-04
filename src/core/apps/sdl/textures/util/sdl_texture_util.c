#ifdef zoxel_using_sdl_images

    SDL_Surface* load_png_as_surface(const char *filepath) {
        return (SDL_Surface*) IMG_Load(filepath);
    }

    void save_texture_as_png(const TextureData *textureData, const TextureSize *textureSize, const char *outputTextureName) {
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
        if(IMG_SavePNG(surface, outputTextureName) != 0) {
            // Error saving bitmap
            zoxel_log(" ! failed with [IMG_SavePNG]: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }

#else

    SDL_Surface* load_png_as_surface(const char *filepath) {
        return NULL;
    }

    void save_texture_as_png(const TextureData *textureData, const TextureSize *textureSize, const char *outputTextureName) { }

#endif

void load_app_icon(SDL_Window* window, const char *icon_filepath) {
    SDL_Surface *surface = load_png_as_surface(icon_filepath); // IMG_Load(icon_filepath); // IMG_Load(buffer);
    if (surface != NULL) {
        SDL_SetWindowIcon(window, surface); // The icon is attached to the window pointer
        SDL_FreeSurface(surface);
    }
}
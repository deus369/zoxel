/*SDL_Cursor* sdl_cursor;

float4 Uint32ToFloat4(Uint32 color) {
    float4 result;
    // Extract individual color components
    Uint8 r = (color >> 24) & 0xFF;
    Uint8 g = (color >> 16) & 0xFF;
    Uint8 b = (color >> 8) & 0xFF;
    Uint8 a = color & 0xFF;
    // Convert to float and normalize to 0.0 - 1.0 range
    result.x = r / 255.0f;
    result.y = g / 255.0f;
    result.z = b / 255.0f;
    result.w = a / 255.0f;
    return result;
}

extern color float4_to_color(const float4 input);

// Function to create a cursor from an SDL texture
SDL_Cursor* create_sdl_cursor(const char* path, const int2 hotspot) {
#ifndef zox_sdl_images
    return NULL;
#else
    // SDL_Surface* surface = IMG_Load(path);
    // SDL_Surface* surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if (!surface) {
        printf(" ! IMG_Load: %s\n", IMG_GetError());
        return NULL;
    }
    // Lock the surface for pixel manipulation
    SDL_LockSurface(surface);
    // Get a pointer to the pixel data
    Uint32* pixels = (Uint32*)surface->pixels;
    pixels[0] = SDL_MapRGBA(surface->format, 0, 0, 0, 0);
    // Unlock the surface
    SDL_UnlockSurface(surface);

    // SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB4444, 0);
    // SDL_FreeSurface(surface);
    // surface = converted;
    SDL_Cursor* cursor = SDL_CreateColorCursor(surface, hotspot.x, hotspot.y);
    SDL_FreeSurface(surface);
    if (!cursor) printf(" ! SDL_CreateColorCursor: %s\n", SDL_GetError());
    return cursor;
#endif
}

void dispose_sdl_cursor() {
    if (sdl_cursor) SDL_FreeCursor(sdl_cursor);
}

void set_sdl_cursor(const char* path, const int2 hotspot) {
    zox_log(" > sdl cursor loading from [%s]\n", path)
    SDL_Cursor* cursor = create_sdl_cursor(path, hotspot);
    if (!cursor) {
        zox_log(" ! set_sdl_cursor error: cursor null\n")
        return;
    }
    SDL_SetCursor(cursor);
    dispose_sdl_cursor();
    sdl_cursor = cursor;
}
*/

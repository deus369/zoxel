SDL_Cursor* sdl_cursor;

// Function to create a cursor from an SDL texture
SDL_Cursor* create_sdl_cursor(const char* path, const int2 hotspot) {
#ifndef zox_lib_sdl_images
    return NULL;
#else
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        printf(" ! IMG_Load: %s\n", IMG_GetError());
        return NULL;
    }
    SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB4444, 0);
    SDL_FreeSurface(surface);
    surface = converted;
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
    SDL_Cursor* cursor = create_sdl_cursor(path, hotspot);
    if (!cursor) return;
    SDL_SetCursor(cursor);
    dispose_sdl_cursor();
    sdl_cursor = cursor;
}

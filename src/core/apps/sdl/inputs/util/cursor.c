SDL_Cursor* sdl_cursor;

// Function to create a cursor from an SDL texture
SDL_Cursor* create_sdl_cursor(const char* path, const int2 hotspot) {
#ifndef zox_lib_sdl_images
    return NULL;
#else
    // Load the image as a surface
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("IMG_Load: %s\n", IMG_GetError());
        return NULL;
    }
    // Create a cursor from the surface
    SDL_Cursor* cursor = SDL_CreateColorCursor(surface, hotspot.x, hotspot.y);
    if (!cursor) SDL_Log("SDL_CreateColorCursor: %s\n", SDL_GetError());
    // Free the surface since the cursor now has its own copy
    SDL_FreeSurface(surface);
    return cursor;
#endif
}

void dispose_sdl_cursor() {
    if (sdl_cursor) SDL_FreeCursor(sdl_cursor);
}

void set_sdl_cursor(const char* path, const int2 hotspot) {
    SDL_Cursor* cursor = create_sdl_cursor(path, hotspot);
    if (!cursor) return;
    // Set the cursor
    SDL_SetCursor(cursor);
    dispose_sdl_cursor();
    sdl_cursor = cursor;
}

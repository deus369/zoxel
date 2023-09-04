const char *icon_filepath;

void load_app_icon(SDL_Window* window) {
    #ifdef SDL_IMAGES
        SDL_Surface *surface = IMG_Load(icon_filepath); // IMG_Load(buffer);
        SDL_SetWindowIcon(window, surface); // The icon is attached to the window pointer
        SDL_FreeSurface(surface);
    #endif
}
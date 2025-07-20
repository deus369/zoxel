//! Save PNG to file using SDL
/**
 * https://wiki.libsdl.org/SDL_CreateTexture
 * https://wiki.libsdl.org/SDL_UpdateTexture
*/
// https://wiki.libsdl.org/SDL_PixelFormatEnum
// int req_format = STBI_rgb_alpha;

/*
extern SDL_Renderer *renderer;
SDL_Texture* sdlTexture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_RGBA32,
    SDL_TEXTUREACCESS_STATIC,
    textureSize->value.x,
    textureSize->value.y);*/

// SDL_Rect sdlRect = { 0, 0, textureSize->value.x, textureSize->value.y };
// SDL_UpdateTexture(sdlTexture, &sdlRect, &textureData->value, textureSize->value.x * 4);
// SDL_Surface* surface = SDL_LoadBMP("image.bmp");
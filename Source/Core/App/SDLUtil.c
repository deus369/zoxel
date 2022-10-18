#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#ifdef SDL_IMAGES
#include <SDL2/SDL_image.h>
#endif

const char *iconFilename = "Resources/Textures/GameIcon.png";
int2 screenDimensions = { 480, 480 };
float aspectRatio = 1;
float fov = 60;
SDL_Window* window;
SDL_Renderer *renderer;
SDL_GLContext context;
unsigned long windowFlags;
// forward declarations
void LoadIconSDL(SDL_Window* window);

//! Zoxel can also be a command tool... Wuut?!?!!
void PrintHelpMenu(const char* arg0)
{
    printf("\n");
    printf("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    printf("\n");
    printf("Welcome to Zoxel Help Menu\n\n");
    printf("    Usage: %s [options]\n", arg0);
    printf("\n");
    printf("    Options:\n");
    printf("\n");
    printf("        -h --help        print this help\n");
    printf("        -f --fullscreen  fullscreen window\n");
    printf("        -v --vsync       enable vsync\n");
    printf("        -p --profiler       enable profiler\n");
    printf("\n");
    printf("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    printf("\n");
}

//! Print debug info!
void PrintSDLDebug()
{
    printf("Platform:        %s\n", SDL_GetPlatform());
    printf("    CPU Count:       %d\n", SDL_GetCPUCount());
    printf("    System RAM:      %d MB\n", SDL_GetSystemRAM());
    printf("    Supports SSE:    %s\n", SDL_HasSSE() ? "true" : "false");
    printf("    Supports SSE2:   %s\n", SDL_HasSSE2() ? "true" : "false");
    printf("    Supports SSE3:   %s\n", SDL_HasSSE3() ? "true" : "false");
    printf("    Supports SSE4.1: %s\n", SDL_HasSSE41() ? "true" : "false");
    printf("    Supports SSE4.2: %s\n", SDL_HasSSE42() ? "true" : "false");
}

//! Initialize SDL things, thingy things.
int SetSDLAttributes(bool vsync)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Failed to Initialize SDL2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Request at least 32-bit color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Request a double-buffered, OpenGL 3.3 (or higher) core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
// #ifdef __EMSCRIPTEN__
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
// #else
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
// #endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_RENDERER_SOFTWARE SDL_RENDERER_ACCELERATED
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);
    return EXIT_SUCCESS;
}

//! Spawn the SDL Window.
int SpawnWindowSDL(bool fullscreen)
{
    // SDL_CreateWindowAndRenderer(screenDimensions.x, screenDimensions.y, 0, &window, &renderer);
    /*windowFlags = SDL_WINDOW_OPENGL;
    SDL_CreateWindow("Zoxel",
         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         screenDimensions.x, screenDimensions.y, windowFlags);
    context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        return -1;
    }*/
    windowFlags = SDL_WINDOW_OPENGL;
    if (fullscreen) 
    {
        windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    window = SDL_CreateWindow("Zoxel",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        screenDimensions.x, screenDimensions.y, windowFlags);
    if (window == NULL)
    {
        SDL_Quit();
        fprintf(stderr, "Failed to Create Window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // SDL_GLContext is an alias for "void*"
    context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        // common error: EGL_BAD_MATCH
        SDL_DestroyWindow(window);
        SDL_Quit();
        fprintf(stderr, "Failed to Create OpenGL Context: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_GL_SetSwapInterval(1);
    LoadIconSDL(window);
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_GL_SwapWindow(window);
    return EXIT_SUCCESS;
}

void UpdateLoopSDL()
{
    SDL_GL_SwapWindow(window);
}

void EndSDL()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (context)
    {
        SDL_GL_DeleteContext(context);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//! Loads a Game Icon from the ui-icons folder.
void LoadIconSDL(SDL_Window* window)
{
#ifdef SDL_IMAGES
    SDL_Surface *surface = IMG_Load(iconFilename); // IMG_Load(buffer);
    // The icon is attached to the window pointer
    SDL_SetWindowIcon(window, surface);
    // ...and the surface containing the icon pixel data is no longer required.
    SDL_FreeSurface(surface);
#endif
}

void ResizeOpenGLViewport(int screenWidth, int screenHeight)
{
    screenDimensions.x = screenWidth;
    screenDimensions.y = screenHeight;
    if(screenDimensions.y <= 0)
    {
        screenDimensions.y = 1;
    }
    aspectRatio = ((float)screenDimensions.x) / ((float)screenDimensions.y);
    // printf("Updated Canvas: Screen Dimensions [%i x %i] Aspect Ratio [%f].\n", screenWidth, screenHeight, aspectRatio);
    // what does viewport do? oh well
    glViewport(0, 0, (GLsizei) screenWidth, (GLsizei) screenHeight);
}

/*
//! \todo Multiwindow support. A camera will be hooked up to a window. A window will contain camera links. Trigger those cameras to update screen dimensions there.
printf("Updated Canvas: Screen Dimensions [%i x %i] Aspect Ratio [%f].\n", screenWidth, screenHeight, aspectRatio);
glViewport(0, 0, (GLsizei) screenWidth, (GLsizei) screenHeight);
GluPerspective(fov, aspectRatio, 1.0f, 100.0f);*/

/*glMatrixMode(GL_PROJECTION);
glLoadIdentity();
GluPerspective(fov, aspectRatio, 1.0f, 100.0f);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
printf("Aspect Ratio is now %f.\n", aspectRatio);*/


// glOrtho( 0.0, width, height, 0.0, 1.0, -1.0 );
//  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
// glOrtho(0, width, height, 0, -1.0, 1.0);
// glMatrixMode(GL_PROJECTION);

/*void glhFrustumf2(float *matrix, float left, float right, float bottom, float top, float znear, float zfar)
{
    float temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    matrix[0] = temp / temp2;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 0.0;
    matrix[5] = temp / temp3;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    matrix[8] = (right + left) / temp2;
    matrix[9] = (top + bottom) / temp3;
    matrix[10] = (-zfar - znear) / temp4;
    matrix[11] = -1.0;
    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = (-temp * zfar) / temp4;
    matrix[15] = 0.0;
}

void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio,
                      float znear, float zfar)
{
    float ymax, xmax;
    float temp, temp2, temp3, temp4;
    ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
    // ymin = -ymax;
    // xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    glhFrustumf2(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}*/

// Matrix will receive the calculated perspective matrix.
// You would have to upload to your shader
// or use glLoadMatrixf if you aren't using shaders.
// void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio,
//                       float znear, float zfar)
// {
//     float ymax, xmax;
//     float temp, temp2, temp3, temp4;
//     ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
//     // ymin = -ymax;
//     // xmin = -ymax * aspectRatio;
//     xmax = ymax * aspectRatio;
//     glhFrustumf2(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
// }

// void glhFrustumf2(float *matrix, float left, float right, float bottom, float top,
//                   float znear, float zfar)
// {
//     float temp, temp2, temp3, temp4;
//     temp = 2.0 * znear;
//     temp2 = right - left;
//     temp3 = top - bottom;
//     temp4 = zfar - znear;
//     matrix[0] = temp / temp2;
//     matrix[1] = 0.0;
//     matrix[2] = 0.0;
//     matrix[3] = 0.0;
//     matrix[4] = 0.0;
//     matrix[5] = temp / temp3;
//     matrix[6] = 0.0;
//     matrix[7] = 0.0;
//     matrix[8] = (right + left) / temp2;
//     matrix[9] = (top + bottom) / temp3;
//     matrix[10] = (-zfar - znear) / temp4;
//     matrix[11] = -1.0;
//     matrix[12] = 0.0;
//     matrix[13] = 0.0;
//     matrix[14] = (-temp * zfar) / temp4;
//     matrix[15] = 0.0;
// }


// void ResizeWindow()
// {
//     int screen_width = event.resize.w;
//     int screen_height = event.resize.h;
//     SDL_SetVideoMode(screen_width, screen_height, bpp, SDL_OPENGL | SDL_RESIZABLE | SDL_DOUBLEBUF);
//     glViewport(0, 0, screen_width, screen_height);
//     glMatrixMode(GL_PROJECTION);
//     glOrtho(0, screen_width, 0, screen_height, -1, 1);
//     glLoadIdentity();
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
//     glClear(GL_COLOR_BUFFER_BIT);
//     glLoadIdentity();
// }


// SDL_Surface *IMG_Load(const char *file);
// SDL_Surface *surface;     // Declare an SDL_Surface to be filled in with pixel data from an image file
// Uint16 pixels[16*16] = {  // ...or with raw pixel data:
//     0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
//     0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
//     0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
//     0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
//     0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
//     0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
//     0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
//     0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
//     0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
//     0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
//     0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
//     0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
//     0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
//     0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
//     0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
//     0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
//     0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
//     0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
//     0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
//     0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
//     0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
//     0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
//     0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
//     0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
//     0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
//     0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
//     0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
//     0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
//     0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
//     0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
//     0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
//     0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
// };
// surface = SDL_CreateRGBSurfaceFrom(pixels,16,16,16,16*2,0x0f00,0x00f0,0x000f,0xf000);

// void ResizeSDL(SDL_Event *event)
// {
//     //int screen_width = event->window->w;
//     //int screen_height = event->window.h;
//     int screen_width;
//     int screen_height;
//     SDL_GL_GetDrawableSize(window, &screen_width, &screen_height);
//     printf("Resizing Window [%i, %i]", screen_width, screen_height);
// }
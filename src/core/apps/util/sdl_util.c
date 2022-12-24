// sdl util things
#ifdef ANDROID_BUILD
    #define resources_folder_name "android-resources/"
#else
    #define resources_folder_name "resources/"
#endif
#include <dirent.h>
#include <errno.h>

const char *iconFilename = resources_folder_name"textures/game_icon.png";
int2 screen_dimensions = { 720, 480 };
float aspectRatio = 1;
float fov = 60;
unsigned long windowFlags;
char *data_path = NULL;

void set_data_path()
{
    #ifdef ANDROID_BUILD
    char *base_path = SDL_GetPrefPath("libsdl", "app");
    /*char *android_path = SDL_GetBasePath(); // SDL_AndroidGetInternalStoragePath();
    char *base_path = malloc(strlen(android_path) + 1 + 0); // 1
    strcpy(base_path, android_path);
    strcat(base_path, "");  // /*/
    #else
    char *base_path = SDL_GetBasePath();
    #endif
    if (base_path)
    {
        data_path = base_path;
    }
    else
    {
        data_path = SDL_strdup("./");
    }
    DIR* dir = opendir(base_path);
    if (dir)
    {
        #ifdef zoxel_debug_pathing
        zoxel_log_arg("SDL data_path (EXISTS): %s\n", data_path);
        #endif
        /*char *path_test = malloc(strlen(base_path) + 1 + 1);
        strcpy(path_test, base_path);
        strcat(path_test, ".");
        DIR* dir3 = opendir(path_test);
        if (dir3)
        {
            zoxel_log_arg(" -> path_test [%s]\n", path_test);
            struct dirent *dir3_data;
            while ((dir3_data = readdir(dir3)) != NULL)
            {
                zoxel_log_arg("     -> child path [%s]\n", dir3_data->d_name);
            }
            closedir(dir3);
        }
        free(path_test);*/
        char *resources_path = malloc(strlen(base_path) + strlen(resources_folder_name) + 1);
        strcpy(resources_path, base_path);
        strcat(resources_path, resources_folder_name);
        DIR* dir2 = opendir(resources_path);
        if (dir2)
        {
            #ifdef zoxel_debug_pathing
                zoxel_log_arg("resources_path (EXISTS): %s\n", resources_path);
            #endif
            closedir(dir2);
        }
        else
        {
            zoxel_log_arg("resources_path (DOES NOT EXIST): %s\n", resources_path);
        }
        free(resources_path);
    }
    else if (ENOENT == errno)
    {
        zoxel_log_arg("SDL data_path (DOES NOT EXIST): %s\n", data_path);
    }
    else
    {
        zoxel_log_arg("SDL data_path (MYSTERIOUSLY DOES NOT EXIST): %s\n", data_path);
    }
}

char* get_full_file_path(const char* filepath)
{
    char* fullpath = malloc(strlen(data_path) + strlen(filepath) + 1);
    strcpy(fullpath, data_path);
    strcat(fullpath, filepath);
    #ifdef zoxel_debug_pathing
    zoxel_log_arg("fullpath: %s\n", fullpath);
    #endif
    return fullpath;
}

// emscripten app functions
#ifdef WEB_BUILD

EM_JS(int, get_canvas_width, (), { return window.innerWidth; });
EM_JS(int, get_canvas_height, (), { return window.innerHeight; });

// bool isResizeCanvas = false;
int2 get_canvas_size()
{
    return (int2) { get_canvas_width(), get_canvas_height() };
}

// Condensed
void resize_canvas()
{
    zoxel_log_arg("Resizing Canvas [%ix%i]", get_canvas_width(), get_canvas_height());
}
#endif

//! Zoxel can also be a command tool... Wuut?!?!!
void PrintHelpMenu(const char* arg0)
{
    zoxel_log("\n");
    zoxel_log("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    zoxel_log("\n");
    zoxel_log("Welcome to Zoxel Help Menu\n\n");
    zoxel_log_arg("    Usage: %s [options]\n", arg0);
    zoxel_log("\n");
    zoxel_log("    Options:\n");
    zoxel_log("\n");
    zoxel_log("        -h --help        print this help\n");
    zoxel_log("        -f --fullscreen  fullscreen window\n");
    zoxel_log("        -g --halfscreen  halfscreen window\n");
    zoxel_log("        -s --splitscreen split screen local coop\n");
    zoxel_log("        -v --vsync       enable vsync\n");
    zoxel_log("        -p --profiler       enable profiler\n");
    zoxel_log("\n");
    zoxel_log("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    zoxel_log("\n");
}

void SetStartScreenSize()
{
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    screen_dimensions.x = displayMode.w;
    screen_dimensions.y = displayMode.h;
    if (halfscreen)
    {
        screen_dimensions.x /= 2;
        screen_dimensions.y /= 2;
    }
#ifdef WEB_BUILD
    int2 canvas_size = get_canvas_size();
    zoxel_log_arg("    Canvas Screen Dimensions: %ix%i\n", canvas_size.x, canvas_size.y);
    screen_dimensions = canvas_size;
#endif
}

//! Print debug info!
void print_sdl()
{
    #ifdef zoxel_debug_sdl
    zoxel_log("SDL\n");
    zoxel_log_arg("    Platform:        %s\n", SDL_GetPlatform());
    zoxel_log_arg("    CPU Count:       %d\n", SDL_GetCPUCount());
    zoxel_log_arg("    System RAM:      %d MB\n", SDL_GetSystemRAM());
    zoxel_log_arg("    Screen Dimensions: %ix%i\n", screen_dimensions.x, screen_dimensions.y);
    zoxel_log_arg("    Supports SSE:    %s\n", (SDL_HasSSE() ? "true" : "false"));
    zoxel_log_arg("    Supports SSE2:   %s\n", (SDL_HasSSE2() ? "true" : "false"));
    zoxel_log_arg("    Supports SSE3:   %s\n", (SDL_HasSSE3() ? "true" : "false"));
    zoxel_log_arg("    Supports SSE4.1: %s\n", (SDL_HasSSE41() ? "true" : "false"));
    zoxel_log_arg("    Supports SSE4.2: %s\n", (SDL_HasSSE42() ? "true" : "false"));
    #endif
}

void print_opengl()
{
    #ifdef zoxel_debug_opengl
    zoxel_log("OpenGL Context\n");
    zoxel_log_arg("    Vendor:   %s\n", glGetString(GL_VENDOR));
    zoxel_log_arg("    Renderer: %s\n", glGetString(GL_RENDERER));
    zoxel_log_arg("    Version:  %s\n", glGetString(GL_VERSION));
    zoxel_log_arg("    GLSL Version:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    #endif
}

void sdl_toggle_fullscreen(SDL_Window* window)
{
    #ifndef ANDROID_BUILD
        Uint32 fullscreen_flag = SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN;
    #else
        Uint32 fullscreen_flag = SDL_WINDOW_FULLSCREEN;
    #endif
    bool isFullscreen = SDL_GetWindowFlags(window) & fullscreen_flag;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreen_flag);
    // SDL_ShowCursor(isFullscreen);
}

//! Initialize SDL things, thingy things.
int SetSDLAttributes(bool vsync)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        // zoxel_log_arg(stderr, "Failed to Initialize SDL2: %s\n", SDL_GetError());
        zoxel_log_arg("Failed to Initialize SDL2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Request at least 32-bit color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Request a double-buffered, OpenGL 3.3 (or higher) core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_RENDERER_SOFTWARE SDL_RENDERER_ACCELERATED
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);
    return EXIT_SUCCESS;
}

//! Loads a Game Icon from the ui-icons folder.
void LoadIconSDL(SDL_Window* window)
{
#ifdef SDL_IMAGES
    char* fullpath = get_full_file_path(iconFilename);
    SDL_Surface *surface = IMG_Load(iconFilename); // IMG_Load(buffer);
    free(fullpath);
    // The icon is attached to the window pointer
    SDL_SetWindowIcon(window, surface);
    // ...and the surface containing the icon pixel data is no longer required.
    SDL_FreeSurface(surface);
#endif
}

//! Spawn the SDLWindow.
SDL_Window* SpawnWindowSDL(bool fullscreen)
{
    bool is_resizeable = true;
    windowFlags = SDL_WINDOW_OPENGL;
    #ifdef ANDROID_BUILD
        windowFlags = SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN;
        is_resizeable = false;
    #endif
    /*#ifndef WEB_BUILD
    if (fullscreen) 
    {
        printf("Setting fullscreen!\n");
        windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    #endif*/
    // SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    int2 app_position = (int2) { };
    int displays = SDL_GetNumVideoDisplays();
    if (displays > 1 && window_index != -1 && window_index < displays)
    {
        app_position.x = screen_dimensions.x * window_index;
    }
    SDL_Window* window = SDL_CreateWindow("Zoxel",
        app_position.x, app_position.y,
        screen_dimensions.x, screen_dimensions.y, windowFlags);
    if (window == NULL)
    {
        SDL_Quit();
        // fprintf(stderr, "Failed to Create SDLWindow: %s\n", SDL_GetError());
        zoxel_log_arg("Failed to Create SDLWindow: %s\n", SDL_GetError());
        return window;
    }
    SDL_GL_SetSwapInterval(1);
    LoadIconSDL(window);
    SDL_SetWindowResizable(window, is_resizeable); // SDL_TRUE);
    SDL_GL_SwapWindow(window);
    return window;
}

SDL_GLContext* create_sdl_context(SDL_Window* window)
{
    SDL_GLContext* context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        // zoxel_log_arg(stderr, "Failed to Create OpenGL Context: %s\n", SDL_GetError());
        zoxel_log_arg("Failed to Create OpenGL Context: %s\n", SDL_GetError());
    }
    print_opengl();
    return context;
}

SDL_Window* spawn_sdl_window()
{
    int didFail = SetSDLAttributes(vsync);
    SetStartScreenSize();
    print_sdl();
    if (didFail == EXIT_FAILURE)
    {
        zoxel_log("Failed to SetSDLAttributes.");
        return NULL;
    }
    SDL_Window* window = SpawnWindowSDL(fullscreen);
    return window;
}

//! Quits the application from running indefinitely.
void quit()
{
    running = false;
    #ifdef WEB_BUILD
    emscripten_cancel_main_loop();
    #endif
}

extern void input_extract_from_sdl(ecs_world_t *world, SDL_Event event);
extern void input_extract_from_sdl_per_frame(ecs_world_t *world);
extern void resize_cameras(int width, int height);
extern void uis_on_viewport_resized(ecs_world_t *world, int width, int height);

void on_viewport_resized(ecs_world_t *world, int width, int height)
{
    #ifdef debug_viewport_resize
    zoxel_log_arg("Viewport was resized [%ix%i]\n", width, height);
    #endif
    screen_dimensions.x = width;
    screen_dimensions.y = height;
    if(screen_dimensions.y <= 0)
    {
        screen_dimensions.y = 1;
    }
    aspectRatio = ((float)screen_dimensions.x) / ((float)screen_dimensions.y);
    resize_cameras(width, height);
    uis_on_viewport_resized(world, width, height);
}

//! Polls SDL for input events. Also handles resize and window quit events.
void update_sdl(ecs_world_t *world)
{
    input_extract_from_sdl_per_frame(world);
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event))
    {
        input_extract_from_sdl(world, event);
        int eventType = event.type;
        // handles application close button
        if (eventType == SDL_QUIT)
        {
            quit();
        }
        // redo this
        else if (eventType == SDL_KEYUP)
        {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_ESCAPE) 
            {
                quit();
            }
        }
        else if (eventType == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                on_viewport_resized(world, event.window.data1, event.window.data2);
            }
        }
    }
}

//! Convert starting arguments to Settings.
int process_arguments(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            PrintHelpMenu(argv[0]);
            return EXIT_FAILURE;
        }
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fullscreen") == 0)
        {
            fullscreen = true;
        }
        if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--halfscreen") == 0)
        {
            halfscreen = true;
        }
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--splitscreen") == 0)
        {
            is_split_screen = true;
        }
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vsync") == 0)
        {
            vsync = true;
        }
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--profiler") == 0)
        {
            profiler = true;
        }
        if (strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "--headless") == 0)
        {
            headless = true;
        }
    }
    return EXIT_SUCCESS;
}

#ifdef WEB_BUILD

    #define debug_ui_scaling

    bool update_web_canvas(ecs_world_t *world)
    {
        int2 canvas_size = get_canvas_size();
        if (screen_dimensions.x != canvas_size.x || screen_dimensions.y != canvas_size.y)
        {
            zoxel_log_arg("update_web_canvas: Canvas size has changed [%i x %i]\n", canvas_size.x, canvas_size.y);
            on_viewport_resized(world, canvas_size.x, canvas_size.y);
            return true;
        }
        return false;
    }
#endif
// profiling: make build/dev && make run-dev-profiler
// #include "profiler_defines.c"
#include "engine/engine.c"
#include "zoxel/zoxel.c"

#ifdef ANDROID_BUILD
    #include <android/log.h>
    #define APPNAME "Zoxel"
#endif

#ifdef WINDOWS_BUILD
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc = 0;
    char** argv = NULL;
#else
int main(int argc, char* argv[]) {
#endif
    if (begin(argc, argv) == EXIT_SUCCESS) {
        // import game module
        zoxel_import_module(Zoxel)
        main_loop();
        end();
    }
    return 0;
}
// profiling: make build/dev && make run-dev-profiler
// #include "profiler_defines.c"
#include "zoxel_engine.c"
#include "zoxel/zoxel.c"

#ifdef WINDOWS_BUILD
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc = 0;
    char** argv = NULL;
#else
int main(int argc, char* argv[]) {
#endif
    //! Where it all begins and ends.
    if (begin(argc, argv) == EXIT_SUCCESS) {
        zoxel_import_module(Zoxel)       // import game
        main_loop();
        end();
    }
    return 0;
}
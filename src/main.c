// #include "_profiler.c"  // profiling: make build/dev && make run-dev-profiler
#include "_includes.c"

#ifndef _WIN32
int main(int argc, char* argv[])
{
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int argc = 0;
    char** argv = NULL;
#endif
    //! Where it all begins and ends.
    if (begin(argc, argv) == 0)
    {
        zoxel_import_module(Zoxel)       // import game
        main_loop();
        end();
    }
    return 0;
}
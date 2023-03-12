// #include "_profiler.c"  // profiling: make build/dev && make run-dev-profiler
#include "_includes.c"

//! Where it all begins and ends.
int main(int argc, char* argv[])
{
    if (begin(argc, argv) == 0)
    {
        zoxel_import_module(Zoxel)       // import game
        main_loop();
        end();
    }
    return 0;
}
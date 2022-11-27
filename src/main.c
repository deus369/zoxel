#include "_includes.c"

//! Where it all begins and ends.
int main(int argc, char* argv[])
{
    if (begin(argc, argv) == 0)
    {
        ECS_IMPORT(world, Zoxel);       // import game
        main_loop();
        end();
    }
    return 0;
}
//! This script tests running zoxel game very quickly.

// Build:
// cc -std=c99 -D_DEFAULT_SOURCE -o builds/quick_runs include/flecs.c tests/zoxel/quick_runs.c -g -lGL -lSDL2 -lSDL2_image -lSDL2_mixer -lm;
// Run:
// ./builds/quick_runs

#include "../../src/_includes.c"
const int application_runs_count = 32;
const int ecs_cycles_count = 8;

//! Where it all begins and ends.
int main(int argc, char* argv[])
{
    for (int i = 0; i < application_runs_count; i++)
    {
        printf("=========================\n");
        printf("Testing Zoxel [%i]\n\n", i);
        ui_cameras[0] = 0;
        main_cameras[0] = 0;
        running = true;
        if (begin(argc, argv) == 0)
        {
            ECS_IMPORT(world, Zoxel);
            ecs_progress(world, 0);
            for (int j = 0; j < ecs_cycles_count; j++)
            {
                if (running)
                {
                    update();
                }
            }
            end();
        }
        printf("\n=========================\n");
    }
    printf("=========================\n");
    printf("RESULT: SUCCESS\n");
    printf("=========================\n");
    return 0;
}
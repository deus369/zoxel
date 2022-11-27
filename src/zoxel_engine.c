#ifndef zoxel_engine
#define zoxel_engine

// =-= Zoxel Engine =-=
#include "core/core.c"
#include "inner_core/inner_core.c"
#include "outer_core/outer_core.c"
#include "gameplay/gameplay.c"
#include "space/space.c"

int begin(int argc, char* argv[])
{
    return begin_core(argc, argv);
}

void end()
{
    close_core();
}

void update()
{
    update_outer_core();
    update_core();
    update_inner_core();
}

//! Includes special case for emscripten.
void main_loop()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&update, -1, 1); // old - 60, 1);
#else
    while (running)
    {
        update();
    }
#endif
}

void ZoxelEngineImport(ecs_world_t *world)
{
    printf("Importing [Zoxel Engine]\n");
    ECS_MODULE(world, ZoxelEngine);
    ECS_IMPORT(world, Core);
    ECS_IMPORT(world, InnerCore);
    ECS_IMPORT(world, OuterCore);
    ECS_IMPORT(world, Gameplay);
    ECS_IMPORT(world, Space);
}
#endif
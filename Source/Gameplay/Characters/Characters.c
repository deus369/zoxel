#ifndef Zoxel_Characters
#define Zoxel_Characters

// Sub Modules
#include "Characters2D/Characters2D.c"
#include "Characters3D/Characters3D.c"

void CharactersImport(ecs_world_t *world)
{
    ECS_MODULE(world, Characters);
    ECS_IMPORT(world, Characters2D);
    ECS_IMPORT(world, Characters3D);
}
#endif
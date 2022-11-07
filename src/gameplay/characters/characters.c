#ifndef zoxel_characters
#define zoxel_characters

// Sub Modules
#include "characters2D/characters2D.c"
#include "characters3D/characters3D.c"

void CharactersImport(ecs_world_t *world)
{
    ECS_MODULE(world, Characters);
    ECS_IMPORT(world, Characters2D);
    ECS_IMPORT(world, Characters3D);
}
#endif
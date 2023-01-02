#ifndef zoxel_characters
#define zoxel_characters

#include "characters2D/characters2D.c"
#include "characters3D/characters3D.c"

void CharactersImport(ecs_world_t *world)
{
    zoxel_module(Characters)
    zoxel_import_module(Characters2D)
    zoxel_import_module(Characters3D)
}
#endif
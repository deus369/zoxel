#ifndef zoxel_characters
#define zoxel_characters

#include "characters2D/characters2D.c"
#include "characters3D/characters3D.c"

zox_begin_module(Characters)
zox_import_module(Characters2D)
zox_import_module(Characters3D)
zoxel_end_module(Characters)

#endif
/*
 *  Zox Core Two (Inner)
 *
 *      > Textures, Voxels, Music, Animations, UI, Physics, Particles, etc
 *
 *  Somewhat More Reputable
*/
#ifndef zox_mod_inner_core
#define zox_mod_inner_core

#include "textures/textures.c"
#include "musics/musics.c"
#include "animations/animations.c"
#include "ui/ui.c"
#include "lines/lines.c"
#include "plots/plots.c"
#include "genetics/genetics.c"
#include "neurals/neurals.c"
#include "tiles/tiles.c"
#include "voxels/voxels.c"
#include "physics/physics.c"
#include "cubes/cubes.c"
#include "particles/particles.c"
#include "blueprints/blueprints.c"
#include "characters/characters.c"

void update_inner_core(ecs_world_t *world) {
    update_terrain_statistics(); // terrain
}

zox_begin_module(InnerCore)
zox_import_module(Textures)
zox_import_module(Musics)
zox_import_module(Animations)
#ifdef zox_mod_ui
zox_import_module(UI)
#endif
zox_import_module(Lines)
zox_import_module(Plots)
zox_import_module(Genetics)
zox_import_module(Neurals)
zox_import_module(Tiles)
zox_import_module(Voxels)
zox_import_module(Physics)
zox_import_module(Cubes)
zox_import_module(Particles)
zox_import_module(Blueprints)
zox_import_module(Characters)
update_inner_core(world);
zoxel_end_module(InnerCore)

#endif

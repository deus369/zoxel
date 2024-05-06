#ifndef zoxel_inner_core
#define zoxel_inner_core

const char *game_name = "zox";
#include "textures/textures.c"
#include "musics/musics.c"
#include "animations/animations.c"
#include "ui/ui.c"
#include "lines/lines.c"
#include "blueprints/blueprints.c"
#include "genetics/genetics.c"
#include "neurals/neurals.c"
#include "tiles/tiles.c"
#include "voxels/voxels.c"
#include "physics/physics.c"

void dispose_inner_core(ecs_world_t *world) {
    dispose_textures(world);
    dispose_voxes(world);
}

void initialize_inner_core(ecs_world_t *world) {
    initialize_textures(world);
    initialize_ui(world);
    initialize_lines(world);
    initialize_voxes(world);
}

void spawn_prefabs_inner_core(ecs_world_t *world) {
    spawn_prefabs_textures(world);
    spawn_prefabs_ui(world);
    spawn_prefabs_lines(world);
    spawn_prefabs_neurals(world);
    spawn_prefabs_musics(world);
    spawn_prefabs_voxels(world);
}

zox_begin_module(InnerCore)
zox_import_module(Textures)
zox_import_module(Musics)
zox_import_module(Animations)
zox_import_module(UI)
zox_import_module(Lines)
zox_import_module(Blueprints)
zox_import_module(Genetics)
zox_import_module(Neurals)
zox_import_module(Tiles)
zox_import_module(Voxels)
zox_import_module(Physics)
zoxel_end_module(InnerCore)

#endif

#ifndef zox_mod_voxels
#define zox_mod_voxels

zox_component_entity(VoxLink)
#include "blocks/blocks.c"
#include "chunks/chunks.c"
#include "streaming/streaming.c"
#include "structures/structures.c"
#include "animations/voxels_animations.c"
#include "voxes/voxes.c"
#include "terrain/terrain.c"
#include "util/realm_voxels.c"
zox_declare_system_state_event(RealmVoxels, GenerateRealm, zox_generate_realm_voxels, spawn_realm_voxels)

zox_begin_module(Voxels)
    zox_define_component_entity(VoxLink)
    zox_import_module(Blocks)
    zox_import_module(Chunks)
    zox_import_module(Streaming)
    zox_import_module(Structures)
    zox_import_module(VoxelsAnimations)
    zox_import_module(Voxes)
    zox_import_module(Terrain)
    zox_prefab_add(prefab_realm, VoxelLinks)
    zox_prefab_set(prefab_realm, VoxelsDirty, { 0 })
    zox_define_system_state_event_1(RealmVoxels, EcsOnLoad, GenerateRealm)
zoxel_end_module(Voxels)

#endif

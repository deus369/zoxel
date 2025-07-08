#ifndef zox_voxels_blocks
#define zox_voxels_blocks

#include "data/_.c"
#include "components/_.c"
#include "util/generation_util.c"
#include "prefabs/_.c"
#include "systems/terrain_texture_set_system.c"

zox_begin_module(Blocks)
    define_components_blocks(world);
    zox_system(TerrainTextureSetSystem, EcsOnUpdate, [in] realms.RealmLink, [out] textures.core.GenerateTexture, [out] textures.core.TilemapSize, [out] textures.core.TextureLinks, [none] textures.core.Tilemap)
    spawn_prefabs_blocks(world);
zox_end_module(Blocks)

#endif
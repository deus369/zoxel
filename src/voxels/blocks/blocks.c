#ifndef zox_voxels_blocks
#define zox_voxels_blocks

// todo: implement BlockCollider in physics
#include "data/model_types.c"
#include "data/block_types.c"
#include "data/block_sides.c"
#include "data/spawn_block.c"
#include "components/_.c"
#include "util/generation_util.c"
#include "prefabs/prefabs.c"
#include "systems/terrain_texture_set_system.c"

zox_begin_module(Blocks)
    zox_define_components_blocks(world);
    zox_system(TerrainTextureSetSystem, EcsOnUpdate, [in] RealmLink, [out] GenerateTexture, [out] TilemapSize, [out] TextureLinks, [none] textures.core.Tilemap)
    spawn_prefabs_blocks(world);
zox_end_module(Blocks)

#endif
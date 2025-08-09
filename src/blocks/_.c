#ifndef zox_voxels_blocks
#define zox_voxels_blocks

#include "data/_.c"
#include "components/_.c"
#include "util/generation_util.c"
#include "prefabs/_.c"
#include "systems/terrain_texture_set_system.c"

zox_begin_module(Blocks)
    define_components_blocks(world);
    zox_system(TerrainTextureSetSystem, EcsOnUpdate,
        [in] realms.RealmLink,
        [out] textures.GenerateTexture,
        [out] textures.TilemapSize,
        [out] textures.TextureLinks,
        [none] textures.Tilemap);
    add_hook_spawn_prefabs(spawn_prefabs_blocks);
zox_end_module(Blocks)

#endif
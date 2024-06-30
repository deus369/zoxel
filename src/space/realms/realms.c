#if !defined(zox_realms2) && defined(zox_mod_textures)
#define zox_realms2

// todo: Move module to core and add things to realm from modules!
#include "systems/terrain_texture_set_system.c"
#include "util/game_util.c"

zox_begin_module(Realms2)
// zox_pip_texture_generation
zox_system(TerrainTextureSetSystem, EcsOnUpdate, [in] RealmLink, [out] GenerateTexture, [out] TilemapSize, [out] TextureLinks, [none] textures.core.Tilemap)
add_to_event_game_state((zox_game_event) { &realms_game_state });
zoxel_end_module(Realms2)

#endif

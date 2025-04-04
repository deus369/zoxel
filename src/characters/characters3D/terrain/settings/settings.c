// #define zox_enable_log_spawning

byte characters_per_chunk_count = 16; // 0 | 1 | 4 | 8 | 16 | 64
int npc_vox_index_count = 4; // count of below array
char* npc_voxes[] = { "mrpenguin", "slime", "bob", "chicken" };

void set_character_terrain_settings() {
#ifdef zoxel_test_single_character3Ds
    characters_per_chunk_count = 0;
#endif
#ifdef zoxel_debug_settings
    zox_log(" > character terrain settings set\n")
    zox_log("  + character per chunk is [%i]\n", characters_per_chunk_count)
#endif
}

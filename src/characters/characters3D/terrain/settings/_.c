// #define zox_enable_log_spawning
// byte character_spawn_distance = 2;   // not used yet
byte characters_per_chunk_count = 1; // 0 | 1 | 4 | 8 | 16 | 64

int npc_vox_index_count = 5; // count of below array
char* npc_voxes[] = { "mrpenguin", "slime", "bob", "chicken", "tall_cube" };

void print_character_terrain_settings() {
#ifdef zoxel_debug_settings
    zox_log(" > character terrain settings set\n")
    zox_log("  + character per chunk is [%i]\n", characters_per_chunk_count)
#endif
}
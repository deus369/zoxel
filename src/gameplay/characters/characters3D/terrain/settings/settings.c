unsigned char characters_per_chunk_count = 1;
int npc_vox_index_count = 4;
int npc_vox_indexes[] = { 1, 2, 3, 7 }; // penguin | slime | bob | chicken

void set_character_terrain_settings() {
    if (cpu_tier == 3) characters_per_chunk_count = 4;
    else if (cpu_tier == 2) characters_per_chunk_count = 2;
    else if (cpu_tier == 1) characters_per_chunk_count = 1;
    else characters_per_chunk_count = 1;
#ifdef zoxel_test_single_character3Ds
    characters_per_chunk_count = 0;
#endif
#ifdef zoxel_debug_settings
    zoxel_log(" > character terrain settings set\n");
    zoxel_log("     + character per chunk is [%i]\n", characters_per_chunk_count);
#endif
}

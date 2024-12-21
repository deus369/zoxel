// rename dirty to trigger
#define chunk_lod_state_none 0
#define chunk_lod_state_trigger 1

#define chunk_lod_state_generate_trigger 3
#define chunk_lod_state_generate_update 4

// lod updates of prior spawns
#define chunk_lod_state_characters_update 5

// spawning
#define chunk_lod_state_spawning 6
#define chunk_lod_state_characters_spawn 7
#define chunk_lod_state_vox_blocks_pre_spawn 8
#define chunk_lod_state_vox_blocks_spawn 9 // updates lod during spawn step now

// so we can wait for chunks to stream in for neighbors
#define chunk_lod_state_mesh_trigger 10
#define chunk_lod_state_mesh_update 11

#define chunk_lod_state_end 12

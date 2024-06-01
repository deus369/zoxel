// terrain
const int sand_height = -10;
const int mountain_height = 20;
// blocks
#define grass_spawn_chance 90
#define octree_random_spawn_chance 22
#define stone_top_spawn_chance 22
#define grass_vox_spawn_chance 66
#define vox_dirt_spawn_chance 22
#define vox_spawn_chance_dirt_rubble 66
const int test_block_vox_index = 4; // flower
const int test_block_vox_index2 = 6; // little_cube
// voxes lods
const unsigned char max_vox_blocks = 128; // max spawned vox_blocks
const unsigned char block_vox_render_distance = 2; // 3 | 4 looks best
const int init_lod_voxes = 1;
const int lod_div_voxes = 1;
const unsigned char max_lod_voxes = 0;

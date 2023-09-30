// #define texture_update_pipeline 0      // 0 | EcsOnStore | EcsPostUpdate | EcsOnValidate
// long int texture_update_system_id;
// 0 no outline, 1 full outline, 2 half outline, 3 5/6 outline
// textures
#define zox_texture_none 0
#define zox_texture_dirt 1
#define zox_texture_grass 2
#define zox_texture_sand 3
#define zox_texture_stone 4
#define zox_texture_obsidian 5
#define zox_texture_graybox 220
// outline mope
#define zox_outline_type_none 0
#define zox_outline_type_full 1
#define zox_outline_type_half 2
#define zox_outline_type_faded 3
// special modes
#define zox_texture_mode_default 0
#define zox_texture_mode_graybox 1
// settings
unsigned char terrain_texture_outline_type = zox_outline_type_none;
const double noise_animation_speed = 0.5;
unsigned char texture_mode = 0;
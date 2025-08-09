ecs_entity_t local_crosshair;
// layout
const int2 crosshair_pixel_size = { 48, 48 };
// texture
const int2 crosshair_texture_size = { 32, 32 };
const byte crosshair_thickness = 12;
const byte crosshair_corner = 8;
// colors
#define crosshair_alpha 144
const color crosshair_air = { 44, 44, 44, crosshair_alpha };
const color crosshair_terrain = { 44, 122, 122, crosshair_alpha };
const color crosshair_target = { 144, 11, 11, crosshair_alpha };
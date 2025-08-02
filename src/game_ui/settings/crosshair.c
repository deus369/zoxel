ecs_entity_t local_crosshair;
// layout
const int2 crosshair_pixel_size = (int2) { 48, 48 };
// texture
const int2 crosshair_texture_size = (int2) { 32, 32 };
const byte crosshair_thickness = 12;
const byte crosshair_corner = 8;
// colors
#define crosshair_alpha 144
const color crosshair_air = (color) { 44, 44, 44, crosshair_alpha };
const color crosshair_terrain = (color) { 44, 122, 122, crosshair_alpha };
const color crosshair_target = (color) { 144, 11, 11, crosshair_alpha };
ecs_entity_t local_crosshair;
// layout
const int2 crosshair_pixel_size = (int2) { 42, 42 };
// texture
const int2 crosshair_texture_size = (int2) { 32, 32 };
const byte crosshair_thickness = 6;
const byte crosshair_corner = 8;
// colors
const color crosshair_air = (color) { 44, 44, 44, 255 };
const color crosshair_terrain = (color) { 44, 122, 122, 255 };
const color crosshair_target = (color) { 144, 11, 11, 255 };
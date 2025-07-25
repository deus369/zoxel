ecs_entity_t local_crosshair;
// layout
const int2 crosshair_pixel_size = (int2) { 32, 32 };
// texture
const int2 crosshair_texture_size = (int2) { 32, 32 };
const byte crosshair_thickness = 5;
const byte crosshair_corner = 8;
// colors
const color crosshair_air = (color) { 88, 88, 88, 166 };
const color crosshair_terrain = (color) { 44, 88, 88, 155 };
const color crosshair_target = (color) { 113, 11, 11, 177 };
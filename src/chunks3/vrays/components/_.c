#include "raycast.c"

void define_components_vrays(ecs *world) {
    zox_define_component(RaycastVoxelData);
    zox_define_component_float(RaycastRange);
}
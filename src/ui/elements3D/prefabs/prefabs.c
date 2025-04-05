#include "element_world.c"
#include "element_world_child.c"
#include "text3D.c"
#include "zigel3D.c"
#include "elementbar3D_front.c"
#include "elementbar3D.c"
ecs_entity_t prefab_element3D;
ecs_entity_t prefab_element3D_child;
ecs_entity_t prefab_elementbar3D;
ecs_entity_t prefab_elementbar3D_front;
ecs_entity_t prefab_text3D;
ecs_entity_t prefab_zigel3D;

void spawn_prefabs_elements3D(ecs_world_t *world) {
    prefab_element3D = spawn_prefab_element3D(world);
    prefab_element3D_child = spawn_prefab_element3D_child(world);
    prefab_elementbar3D = spawn_prefab_elementbar3D(world, prefab_element3D);
    prefab_elementbar3D_front = spawn_prefab_elementbar3D_front(world, prefab_element3D_child);
    prefab_text3D = spawn_prefab_text3D(world, prefab_element3D_child);
    // prefab_zigel3D = spawn_prefab_zigel3D(world, prefab_element3D_child);
}
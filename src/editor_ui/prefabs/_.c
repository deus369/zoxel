ecs_entity_t prefab_inspector;
ecs_entity_t inspector = 0;
ecs_entity_t prefab_hierarchy;
ecs_entity_t hierarchy;

#include "hierarchy.c"
#include "inspector.c"
#include "profiler.c"

void spawn_prefabs_editor(ecs_world_t *world) {
    prefab_hierarchy = spawn_prefab_hierarchy(world);
    prefab_inspector = spawn_prefab_inspector(world);
}
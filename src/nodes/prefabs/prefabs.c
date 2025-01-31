#include "node.c"
#include "nodelink.c"
#include "nodegraph.c"
ecs_entity_t prefab_node;
ecs_entity_t prefab_nodelink;
ecs_entity_t prefab_nodegraph;

void spawn_prefabs_nodes(ecs_world_t *world) {
    prefab_node = spawn_prefab_node(world);
    prefab_nodelink = spawn_prefab_nodelink(world);
    prefab_nodegraph = spawn_prefab_nodegraph(world);
}

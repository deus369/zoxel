#include "bluenode.c"
#include "blueprint.c"
#include "bluelink.c"
ecs_entity_t prefab_blueprint;
ecs_entity_t prefab_bluenode;
ecs_entity_t prefab_bluelink;

void spawn_prefabs_blueprints(ecs_world_t *world) {
    prefab_bluenode = spawn_prefab_bluenode(world, prefab_node);
    prefab_bluelink = spawn_prefab_bluelink(world, prefab_nodelink);
    prefab_blueprint = spawn_prefab_blueprint(world, prefab_nodegraph);
}

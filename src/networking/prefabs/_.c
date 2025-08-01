#include "packet.c"
#include "net_player.c"
#include "net_room.c"

ecs_entity_t prefab_net_player;
ecs_entity_t prefab_net_room;

void spawn_prefabs_networking(ecs_world_t *world) {
    prefab_net_room = spawn_prefab_net_room(world);
    prefab_net_player = spawn_prefab_net_player(world);
}
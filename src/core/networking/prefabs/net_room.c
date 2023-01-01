ecs_entity_t prefab_net_room;

ecs_entity_t spawn_prefab_net_room(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "prefab_net_room");
    set_unique_entity_name(world, e, "prefab_net_room");
    zoxel_add_tag(world, e, NetRoom);
    zoxel_add_tag(world, e, PacketReciever);
    zoxel_add_tag(world, e, PacketSender);
    zoxel_add(world, e, NetAddress);
    zoxel_add(world, e, NetPort);
    zoxel_set(world, e, SocketLink, { -1 });
    zoxel_set(world, e, Children, { 0, NULL}); // net players will be children of a room
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab net_room [%lu].\n", (long int) (e));
    #endif
    prefab_net_room = e;
    return e;
}

ecs_entity_t spawn_net_room(ecs_world_t *world, int port)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_net_room);
    set_unique_entity_name(world, e, "net_room");
    ecs_set(world, e, NetPort, { port });
    set_new_socket(world, e, port);
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned net_room [%lu]\n", (long int) e);
    #endif
    return e;
}
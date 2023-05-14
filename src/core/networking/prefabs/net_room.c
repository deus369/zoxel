ecs_entity_t prefab_net_room;

ecs_entity_t spawn_prefab_net_room(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_net_room");
    zox_add_tag(e, NetRoom);
    zox_add_tag(e, PacketReciever);
    zox_add_tag(e, PacketSender);
    zox_add(e, NetAddress);
    zox_add(e, NetPort);
    zox_set(e, SocketLink, { -1 });
    zox_set(e, Children, { 0, NULL}); // net players will be children of a room
    ecs_defer_end(world);
    prefab_net_room = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab net_room [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_net_room(ecs_world_t *world, int port) {
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
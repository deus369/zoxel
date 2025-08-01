ecs_entity_t spawn_prefab_net_room(ecs_world_t *world) {
    zox_prefab();
    zox_prefab_name("net_room");
    zox_add_tag(e, NetRoom);
    zox_add_tag(e, PacketReciever);
    zox_add_tag(e, PacketSender);
    zox_prefab_add(e, NetAddress);
    zox_prefab_add(e, NetPort);
    zox_prefab_set(e, SocketLink, { -1 });
    zox_prefab_set(e, Children, { 0, NULL });
    // zox_prefab_add(e, Children);
    return e;
}

ecs_entity_t spawn_net_room(ecs_world_t *world, ecs_entity_t prefab, const int port) {
    zox_instance(prefab);
    zox_name("net_room");
    zox_set(e, NetPort, { port })
    set_new_socket(world, e, port);
    return e;
}

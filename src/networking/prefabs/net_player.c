ecs_entity_t prefab_net_player;

ecs_entity_t spawn_prefab_net_player(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_net_player")
    zox_add_tag(e, NetPlayer)
    zox_add_tag(e, PacketReciever)
    zox_add_tag(e, PacketSender)
    zox_add(e, NetAddress)
    zox_add(e, NetPort)
    zox_add(e, TargetNetAddress)
    zox_add(e, TargetNetPort)
    zox_prefab_set(e, SocketLink, { -1 })
    prefab_net_player = e;
    return e;
}

ecs_entity_t spawn_net_player(ecs_world_t *world, int port, byte4 target_ip, int target_port) {
    zox_instance(prefab_net_player)
    zox_name("net_player")
    zox_set(e, NetPort, { port })
    zox_set(e, TargetNetAddress, { target_ip })
    zox_set(e, TargetNetPort, { target_port })
    set_new_socket(world, e, port);
    return e;
}

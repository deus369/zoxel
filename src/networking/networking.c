#ifndef zox_mod_networking
#define zox_mod_networking

// #define zox_testing_networking
#include "settings/includes.c"
#include "settings/settings.c"
#include "settings/packet_types.c"
zox_declare_tag(Packet)
zox_declare_tag(NetRoom)
zox_declare_tag(NetPlayer)
zox_declare_tag(PacketReciever)
zox_declare_tag(PacketSender)
zox_component(NetAddress, byte4)
zox_component(TargetNetAddress, byte4)
zox_component_int(NetPort)
zox_component_int(TargetNetPort)
zox_component_int(SocketLink)
zox_memory_component(PacketData, byte)
#include "util/ip_util.c"
#include "util/socket_util.c"
#include "components/socket_link.c"
#include "prefabs/packet.c"
#include "prefabs/net_player.c"
#include "prefabs/net_room.c"
#include "util/packet_test.c"
#include "systems/packet_send_system.c"
#include "systems/packet_recieve_system.c"

void spawn_prefabs_networking(ecs_world_t *world) {
#ifdef zoxel_on_windows
    initialize_windows_sockets();
#else
    sockets_enabled = 1;
#endif
    spawn_prefab_net_room(world);
    spawn_prefab_net_player(world);
}

void initialize_networking() {
#ifdef zox_testing_networking
    if (server_mode) spawn_net_room(world, SERVER_PORT);
    else spawn_net_player(world, PORT, server_ip, SERVER_PORT);
    if (server_mode) zox_log(" > network server mode activated\n")
    else zox_log(" > network client mode activated\n")
#endif
}

zox_begin_module(Networking)
    zox_define_tag(Packet)
    zox_define_tag(NetRoom)
    zox_define_tag(NetPlayer)
    zox_define_tag(PacketReciever)
    zox_define_tag(PacketSender)
    zox_define_component(NetAddress)
    zox_define_component(TargetNetAddress)
    zox_define_component_int(NetPort)
    zox_define_component_int(TargetNetPort)
    zox_define_memory_component(PacketData)
    zox_define_component_w_dest(SocketLink)
    zox_system(PacketRecieveSystem, EcsOnUpdate, [none] PacketReciever, [in] SocketLink)
    zox_system(PacketSendSystem, EcsOnUpdate, [none] PacketSender, [in] SocketLink, [in] TargetNetAddress, [in] TargetNetPort)
    spawn_prefabs_networking(world);
zox_end_module(Networking)

#endif

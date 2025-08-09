#ifndef zoxm_networking
#define zoxm_networking

byte zox_log_network_errors = 0;
#include "settings/_.c"
#include "settings/packet_types.c"
zox_tag(Packet);
zox_tag(NetRoom);
zox_tag(NetPlayer);
zox_tag(PacketReciever);
zox_tag(PacketSender);
zoxc(NetAddress, byte4);
zoxc(TargetNetAddress, byte4);
zoxc_int(NetPort);
zoxc_int(TargetNetPort);
zoxc_int(SocketLink);
zoxc_arrayd(PacketData, byte)
#include "util/ip_util.c"
#include "util/socket_util.c"
#include "components/socket_link.c"
#include "prefabs/_.c"
#include "util/packet_test.c"
#include "systems/packet_send_system.c"
#include "systems/packet_recieve_system.c"

void initialize_networking(ecs_world_t* world) {
#ifdef zox_windows
    initialize_windows_sockets();
#else
    sockets_enabled = 1;
#endif
    if (server_mode) {
        spawn_net_room(world, prefab_net_room, SERVER_PORT);
    } else {
        spawn_net_player(world, prefab_net_player, PORT, server_ip, SERVER_PORT);
    }
    if (server_mode) {
        zox_log(" > network server mode activated")
    } else {
        zox_log(" > network client mode activated")
    }
}

void on_boot_networking(ecs_world_t* world, ecs_entity_t app) {
    (void) app;
    if (zox_is_networking) {
        initialize_networking(world);
    }
}

zox_begin_module(Networking)
    add_hook_terminal_command(process_arguments_networking);
    add_hook_on_boot(on_boot_networking);
    zox_define_tag(Packet);
    zox_define_tag(NetRoom);
    zox_define_tag(NetPlayer);
    zox_define_tag(PacketReciever);
    zox_define_tag(PacketSender);
    zox_define_component(NetAddress);
    zox_define_component(TargetNetAddress);
    zox_define_component_int(NetPort);
    zox_define_component_int(TargetNetPort);
    zox_define_memory_component(PacketData);
    zox_define_component_w_dest(SocketLink);
    zox_system(PacketRecieveSystem, EcsOnUpdate,
            [in] SocketLink,
            [none] PacketReciever)
    zox_system(PacketSendSystem, EcsOnUpdate,
            [in] SocketLink,
            [in] TargetNetAddress,
            [in] TargetNetPort,
            [none] PacketSender)
    add_hook_spawn_prefabs(spawn_prefabs_networking);
zox_end_module(Networking)

#endif

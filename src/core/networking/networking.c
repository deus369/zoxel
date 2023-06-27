#ifndef zoxel_networking
#define zoxel_networking

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif
#include <fcntl.h>  // F_SETFL etc
#include <unistd.h> // close function kept here
// atm using 127.0.0.1 for same machine testing
// later for secure packets, keep sending with udp every x seconds
#define IP_TO (byte4) { 127, 0, 0, 1 }  //  "192.0.2.1"
#define PORT 12345
#define SERVER_PORT 12346
#define BUFFER_SIZE 128 // 1024 // the size of the buffer to use for receiving and sending data
//! \todo Convert url to public IP4 address
#define ZOXEL_URL "https://zoxel.duckdns.org"
zox_declare_tag(Packet)
zox_declare_tag(NetRoom)
zox_declare_tag(NetPlayer)
zox_declare_tag(PacketReciever)
zox_declare_tag(PacketSender)
zox_component(NetAddress, byte4)
zox_component(NetPort, int)
zox_component(TargetNetAddress, byte4)
zox_component(TargetNetPort, int)
zox_memory_component(PacketData, unsigned char)
#include "util/ip_util.c"
#include "util/socket_util.c"
#include "components/socket_link.c"
#include "prefabs/packet.c"
#include "prefabs/net_player.c"
#include "prefabs/net_room.c"
#include "util/packet_types.c"
#include "util/packet_test.c"
#include "systems/packet_send_system.c"
#include "systems/packet_recieve_system.c"

void spawn_prefabs_networking(ecs_world_t *world) {
    spawn_prefab_net_room(world);
    spawn_prefab_net_player(world);
    zox_define_destruction(SocketLink)  // for some reason it calls destruction when making prefabs
    #ifdef zoxel_test_networking
        if (server_mode) {
            spawn_net_room(world, SERVER_PORT);
        } else {
            spawn_net_player(world, PORT, IP_TO, SERVER_PORT);
        }
    #endif
}

zox_begin_module(Networking)
if (server_mode) {
    zoxel_log("Server mode activated.\n");
    zoxel_log("Recieving packets.\n");
}
zox_define_tag(Packet)
zox_define_tag(NetRoom)
zox_define_tag(NetPlayer)
zox_define_tag(PacketReciever)
zox_define_tag(PacketSender)
zox_define_component(NetAddress)
zox_define_component(NetPort)
zox_define_component(TargetNetAddress)
zox_define_component(TargetNetPort)
zox_define_memory_component(PacketData)
// zox_define_component_w_dest(SocketLink)
zox_define_component(SocketLink)
zox_system(PacketRecieveSystem, EcsOnUpdate, [none] PacketReciever, [in] SocketLink)
zox_system(PacketSendSystem, EcsOnUpdate, [none] PacketSender, [in] SocketLink, [in] TargetNetAddress, [in] TargetNetPort)
zoxel_end_module(Networking)

#endif
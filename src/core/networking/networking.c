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
// atm using 127.0.0.1 for same machine testing
// later for secure packets, keep sending with udp every x seconds
#define IP_TO (byte4) { 127, 0, 0, 1 }  //  "192.0.2.1"
#define PORT 12345
#define SERVER_PORT 12346
#define BUFFER_SIZE 128 // 1024 // the size of the buffer to use for receiving and sending data
//! \todo Convert url to public IP4 address
#define ZOXEL_URL "https://zoxel.duckdns.org"
zoxel_declare_tag(Packet)
zoxel_declare_tag(NetRoom)
zoxel_declare_tag(NetPlayer)
zoxel_declare_tag(PacketReciever)
zoxel_declare_tag(PacketSender)
zoxel_component(NetAddress, byte4)
zoxel_component(NetPort, int)
zoxel_component(TargetNetAddress, byte4)
zoxel_component(TargetNetPort, int)
zoxel_memory_component(PacketData, unsigned char)
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

zoxel_begin_module(Networking)
if (server_mode) {
    zoxel_log("Server mode activated.\n");
    zoxel_log("Recieving packets.\n");
}
zoxel_define_tag(Packet)
zoxel_define_tag(NetRoom)
zoxel_define_tag(NetPlayer)
zoxel_define_tag(PacketReciever)
zoxel_define_tag(PacketSender)
zoxel_define_component(NetAddress)
zoxel_define_component(NetPort)
zoxel_define_component(TargetNetAddress)
zoxel_define_component(TargetNetPort)
zoxel_define_component(SocketLink)
zoxel_define_memory_component(PacketData);
ecs_set_hooks(world, SocketLink, { .dtor = ecs_dtor(SocketLink) });
zoxel_system(world, PacketRecieveSystem, EcsOnUpdate, [none] PacketReciever, [in] SocketLink);
zoxel_system(world, PacketSendSystem, EcsOnUpdate, [none] PacketSender, [in] SocketLink, [in] TargetNetAddress, [in] TargetNetPort);
spawn_prefab_net_player(world);
spawn_prefab_net_room(world);
#ifdef zoxel_test_networking
if (server_mode) {
    spawn_net_room(world, SERVER_PORT);
} else {
    spawn_net_player(world, PORT, IP_TO, SERVER_PORT);
}
#endif
zoxel_end_module(Networking)

#endif
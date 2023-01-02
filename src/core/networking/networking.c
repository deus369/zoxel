#ifndef zoxel_networking
#define zoxel_networking

// atm using 127.0.0.1 for same machine testing
#define IP_TO (byte4) { 127, 0, 0, 1 }  //  "192.0.2.1"
#define PORT 12345
#define SERVER_PORT 12346
#define BUFFER_SIZE 128 // 1024 // the size of the buffer to use for receiving and sending data
//! \todo Convert url to public IP4 address
#define ZOXEL_URL "https://zoxel.duckdns.org"
// -=- Tags -=-
ECS_DECLARE(Packet);
ECS_DECLARE(NetRoom);
ECS_DECLARE(NetPlayer);
ECS_DECLARE(PacketReciever);
ECS_DECLARE(PacketSender);
// -=- components -=-
zoxel_component(NetAddress, byte4);
zoxel_component(NetPort, int);
zoxel_component(TargetNetAddress, byte4);
zoxel_component(TargetNetPort, int);
// later for secure packets, keep sending with udp every x seconds
zoxel_memory_component(PacketData, unsigned char);
#include "util/ip_util.c"
#include "util/socket_util.c"
#include "components/socket_link.c"
// -=- prefabs -=-
#include "prefabs/packet.c"
#include "prefabs/net_player.c"
#include "prefabs/net_room.c"
// -=- util -=-
#include "util/packet_types.c"
#include "util/packet_test.c"
// -=- systems -=-
#include "systems/packet_send_system.c"
#include "systems/packet_recieve_system.c"

void NetworkingImport(ecs_world_t *world)
{
    zoxel_module(Networking)
    if (server_mode)
    {
        zoxel_log("Server mode activated.\n");
        zoxel_log("Recieving packets.\n");
    }
    // zoxel_module(world, cameras, nm_zoxel_cameras);
    // -=- tags -=-
    ECS_TAG_DEFINE(world, Packet);
    ECS_TAG_DEFINE(world, NetRoom);
    ECS_TAG_DEFINE(world, NetPlayer);
    ECS_TAG_DEFINE(world, PacketReciever);
    ECS_TAG_DEFINE(world, PacketSender);
    // -=- components -=-
    ECS_COMPONENT_DEFINE(world, NetAddress);
    ECS_COMPONENT_DEFINE(world, NetPort);
    ECS_COMPONENT_DEFINE(world, TargetNetAddress);
    ECS_COMPONENT_DEFINE(world, TargetNetPort);
    zoxel_memory_component_define(world, PacketData);
    ECS_COMPONENT_DEFINE(world, SocketLink);
    ecs_set_hooks(world, SocketLink, { .dtor = ecs_dtor(SocketLink) });
    // -=- systems -=-
    zoxel_system(world, PacketRecieveSystem, EcsOnUpdate, [none] PacketReciever, [in] SocketLink);  // , [in] NetAddress
    zoxel_system(world, PacketSendSystem, EcsOnUpdate, [none] PacketSender, [in] SocketLink,
        [in] TargetNetAddress, [in] TargetNetPort);
    // -=- prefabs -=-
    spawn_prefab_net_player(world);
    spawn_prefab_net_room(world);
    #ifdef zoxel_test_networking
        if (server_mode)
        {
            spawn_net_room(world, SERVER_PORT);
        }
        else
        {
            spawn_net_player(world, PORT, IP_TO, SERVER_PORT);
        }
    #endif
}
#endif
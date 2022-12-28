#ifndef zoxel_networking
#define zoxel_networking

// #define zoxel_is_server
#define zoxel_test_send_packet

#ifdef zoxel_is_server
    #define PORT 12345
    #define PORT_TO 12346
#else
    #define PORT 12346
    #define PORT_TO 12345
#endif
#define IP_TO "127.0.0.1" // "192.0.2.1"
#define BUFFER_SIZE 1024 // the size of the buffer to use for receiving and sending data
int sock;
// -=- Tags -=-
ECS_DECLARE(Packet);
ECS_DECLARE(NetServer);
ECS_DECLARE(NetPlayer);
ECS_DECLARE(PacketReciever);
// ECS_DECLARE(Room);
// -=- components -=-
zoxel_component(NetAddress, byte4);
zoxel_memory_component(PacketData, unsigned char);
// -=- prefabs -=-
#include "prefabs/packet.c"
#include "prefabs/net_player.c"
// -=- util -=-
#include "util/packet_test.c"
#include "util/socket_util.c"
// -=- systems -=-
#include "systems/packet_send_system.c"
#include "systems/packet_recieve_system.c"

void close_networking()
{
    // close the socket
    close(sock);
}

void NetworkingImport(ecs_world_t *world)
{
    ECS_MODULE(world, Networking);
    // zoxel_module(world, cameras, nm_zoxel_cameras);
    // -=- tags -=-
    ECS_TAG_DEFINE(world, Packet);
    ECS_TAG_DEFINE(world, NetServer);
    ECS_TAG_DEFINE(world, NetPlayer);
    ECS_TAG_DEFINE(world, PacketReciever);
    // -=- components -=-
    ECS_COMPONENT_DEFINE(world, NetAddress);
    zoxel_memory_component_define(world, PacketData);
    // -=- systems -=-
    #ifndef zoxel_is_server
        // zoxel_system_main_thread
        zoxel_system(world, PacketRecieveSystem, EcsOnUpdate, [none] PacketReciever, [in] NetAddress);
    #endif
    //, [in] FreeRoam, [in] CameraTarget, [out] Position, [out] Rotation)
    // -=- prefabs -=-
    spawn_prefab_net_player(world);
    spawn_net_player(world);
    // testing
    open_socket();
    #ifdef zoxel_test_send_packet
        run_packet_test();
    #endif
}
#endif
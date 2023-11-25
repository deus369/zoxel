#ifndef zoxel_networking
#define zoxel_networking

// backend todo:
//      - use raw packets for relaying character positions (per frame data)
//      > create a test packet system, similar to the send system, used to test limits of packets

// connections / pinging todo:
//      > create an entity for a connection
//      > create a ping client system, that keeps bouncing packets to a connection, if no reply back for x seconds, disconnect
//      > create ping host system, recieves pings, replies
//      > create ping host disconnect system, if no pings for x seconds, disconnect

// secured packets todo:
//      - use this for connecting to host and messages
//      > secure sending -> uses a unique id on a packet, keeps sending
//      > secure recieving -> stores dictionary of packets recieved for up to x seconds, removes duplicates
//      > secure packet host clean system -> removes stored secured packets after x seconds

// front end todo:
//      > create a chat ui, it creates a net player room
//      > when window closes, destroy room, including all players
//      > when connecting confirmed, server will send all other netplayer data to the new client
//      > when new player joins, server will send all the new player data to all other clients
//      > debug connected players using game debug ui, or a new debug ui module with a label type prefab and system

// zoxel_settings_includes
extern unsigned char headless;
#include "settings/includes.c"
#include "settings/settings.c"
#include "settings/packet_types.c"
// zoxel_declare_components
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
// zoxel_include_functions
#include "util/ip_util.c"
#include "util/socket_util.c"
#include "components/socket_link.c"
// zoxel_include_prefabs
#include "prefabs/packet.c"
#include "prefabs/net_player.c"
#include "prefabs/net_room.c"
// zoxel_include_util
#include "util/packet_test.c"
// zoxel_include_systems
#include "systems/packet_send_system.c"
#include "systems/packet_recieve_system.c"

void spawn_prefabs_networking(ecs_world_t *world) {
    spawn_prefab_net_room(world);
    spawn_prefab_net_player(world);
#ifndef zoxel_on_windows
    zox_define_destruction(SocketLink)  // for some reason it calls destruction when making prefabs, so we put these after
#else
    zox_logg("  > todo: get zox_define_destruction(SocketLink) to work on windows.\n")
#endif
    // #ifdef zoxel_test_networking
    if (headless) {
        if (server_mode) spawn_net_room(world, SERVER_PORT);
        else spawn_net_player(world, PORT, IP_TO, SERVER_PORT);
        if (server_mode) zox_logg(" > network server mode activated\n")
        else zox_logg(" > network client mode activated\n")
    }
}

zox_begin_module(Networking)
// zoxel_define_components
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
zox_define_component(SocketLink)
// zox_define_component_w_dest(SocketLink)
// zoxel_define_systems
zox_system(PacketRecieveSystem, EcsOnUpdate, [none] PacketReciever, [in] SocketLink)
zox_system(PacketSendSystem, EcsOnUpdate, [none] PacketSender, [in] SocketLink, [in] TargetNetAddress, [in] TargetNetPort)
zoxel_end_module(Networking)

#endif

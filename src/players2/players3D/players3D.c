#ifndef zox_mod_players3D
#define zox_mod_players3D

#include "data/settings.c"
zox_declare_tag(Player3D)
zox_declare_tag(PlayerCharacter3D)
#include "prefabs/prefabs.c"
#include "util/attach3D.c"
#include "util/labels.c"
#include "systems/player3D_move_system.c"
#include "systems/player3D_rotate_system.c"
#include "systems/player3D_jump_system.c"
#include "systems/player3D_trigger_system.c"

zox_begin_module(Players3D)
    zox_define_tag(Player3D)
    zox_define_tag(PlayerCharacter3D)
    zox_system(Player3DMoveSystem, zox_pip_player_movement, [in] DeviceLinks, [in] DeviceMode, [in] CharacterLink, [none] players.Player)
    zox_system(Player3DRotateSystem, zox_pip_player_movement, [in] DeviceLinks, [in] DeviceMode, [in] CharacterLink, [in] CameraLink, [none] players.Player)
    zox_system(Player3DJumpSystem, zox_pip_player_movement, [in] DeviceLinks, [in] DeviceMode, [in] CharacterLink, [none] players.Player)
    zox_system(Player3DTriggerSystem, EcsPostUpdate, [in] DeviceLinks, [in] DeviceMode, [in] CharacterLink, [none] players.Player)
    spawn_prefabs_players3D(world);
zoxel_end_module(Players3D)

#endif

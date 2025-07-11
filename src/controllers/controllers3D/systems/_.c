#include "player3D_move_system.c"
#include "player3D_rotate_system.c"
#include "player3D_jump_system.c"
#include "player3D_trigger_system.c"

void define_systems_controllers3D(ecs_world_t *world) {
    zox_system(Player3DMoveSystem, zox_pip_player_movement, [in] inputs.DeviceLinks, [in] inputs.DeviceMode, [in] characters.CharacterLink, [none] players.Player)
    zox_system(Player3DRotateSystem, zox_pip_player_movement, [in] inputs.DeviceLinks, [in] inputs.DeviceMode, [in] characters.CharacterLink, [in] cameras.CameraLink, [none] players.Player)
    zox_system(Player3DJumpSystem, zox_pip_player_movement, [in] inputs.DeviceLinks, [in] inputs.DeviceMode, [in] characters.CharacterLink, [none] players.Player)
    zox_system(Player3DTriggerSystem, EcsPostUpdate, [in] inputs.DeviceLinks, [in] inputs.DeviceMode, [in] characters.CharacterLink, [none] players.Player)
}
#ifndef zox_mod_controllers3D
#define zox_mod_controllers3D

#include "data/settings.c"
zox_declare_tag(Player3D)
zox_declare_tag(PlayerCharacter3D)
#include "prefabs/prefabs.c"
#include "util/attach3D.c"
#include "util/labels.c"
#include "systems/systems.c"

zox_begin_module(Controllers3D)
    zox_define_tag(Player3D)
    zox_define_tag(PlayerCharacter3D)
    define_systems_controllers3D(world);
    spawn_prefabs_players3D(world);
zox_end_module(Controllers3D)

#endif
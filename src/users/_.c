#ifndef zoxm_users
#define zoxm_users

zox_component_entity(UserLink)
zox_component_entity(UserDataLink)
zox_component_entity(SpawnerLink)
zox_component_byte(Quantity)
zox_entities_component(UserLinks)
#include "util/user_data.c"
#include "ui/_.c"

zox_begin_module(Users)
    zox_define_component_entity(UserLink)
    zox_define_component_entity(UserDataLink)
    zox_define_component_entity(SpawnerLink)
    zox_define_component_byte(Quantity)
    zox_define_entities_component(UserLinks)
    zox_import_module(UsersUI)
zox_end_module(Users)

#endif

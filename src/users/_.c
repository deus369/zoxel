#ifndef zoxm_users
#define zoxm_users

zoxc_entity(UserLink);
zoxc_entity(UserDataLink);
zoxc_entity(SpawnerLink);
zoxc_byte(Quantity);
zoxc_entities(UserLinks)
#include "util/user_data.c"
#include "ui/_.c"

zox_begin_module(Users)
    zox_define_component_entity(UserLink);
    zox_define_component_entity(UserDataLink);
    zox_define_component_entity(SpawnerLink);
    zoxd_byte(Quantity);
    zox_define_entities_component(UserLinks);
    zox_import_module(UsersUI);
zox_end_module(Users)

#endif

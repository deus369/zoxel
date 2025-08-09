#if !defined(zoxm_players)
#define zoxm_players

// todo: move based functionality into here
#include "states/_.c"
#include "settings/_.c"
zox_tag(Player);
zox_tag(PlayerCharacter);
zoxc_byte(PlayerState);
zoxc_double(PlayerRespawn);
zoxc_entity(PlayerLink);
zoxc_arrayd(PlayerLinks, ecs_entity_t)
zoxc_entity(PlayerPauseEvent);
#include "prefabs/_.c"
#include "spawn/_.c"
#include "systems/_.c"

// int spawn_players(ecs_world_t *world, const ecs_entity_t game);

void add_player(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player) {
    zox_get_muter(e, PlayerLinks, players)
    byte new_length = players->length + 1;
    resize_memory_component(PlayerLinks, players, ecs_entity_t, new_length)
    players->value[new_length - 1] = player;
    zox_set(player, GameLink, { e })
}

int spawn_players(ecs_world_t *world, const ecs_entity_t game) {
    int players = 0;
    if (headless) {
        return players;   // no players in headless mode
    }
    if (is_split_screen) {
        players = 2;
        auto_switch_device = 0;
    }
    else {
        players = 1;
    }
    for (int i = 0; i < players; i++) {
        const ecs_entity_t e = spawn_player(world, prefab_player);
        add_player(world, game, e);
        zox_players[i] = e;
        if (players == 2) {
            if (i == 0) {
                zox_set(e, DeviceModeDirty, { zox_device_mode_keyboardmouse })
            } else if (i == 1) {
                zox_set(e, DeviceModeDirty, { zox_device_mode_gamepad })
            }
        }
        // zox_set(e, CameraLink, { main_cameras[i] });
    }
    return players;
}

void on_boot_players(ecs_world_t *world, ecs_entity_t app) {
    if (!headless && zox_is_players) {
        zox_geter_value(app, GameLink, ecs_entity_t, game)
        spawn_connected_devices(world, app);
        players_playing = spawn_players(world, game);
    }
}

zox_begin_module(Players)
    zox_define_tag(Player);
    zox_define_tag(PlayerCharacter);
    zox_define_component_byte(PlayerState);
    zox_define_component_double(PlayerRespawn);
    zox_define_component_entity(PlayerLink);
    zox_define_memory_component(PlayerLinks);
    zox_define_component_entity(PlayerPauseEvent);
    define_systems_players(world);
    add_hook_on_boot(on_boot_players);
    add_hook_spawn_prefabs(spawn_prefabs_players);
zox_end_module(Players)

#endif

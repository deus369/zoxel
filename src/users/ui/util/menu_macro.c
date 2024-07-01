#define zox_user_menu_functions_minimal(Name, Name2, name, name2)\
\
ecs_entity_t spawn_prefab_menu_##name(ecs_world_t *world, const ecs_entity_t prefab) {\
    zox_prefab_child(prefab)\
    zox_prefab_name("prefab_menu_"#name)\
    zox_add_tag(e, Menu##Name)\
    return e;\
}

#define zox_user_menu_functions(Name, Name2, name, name2)\
\
zox_user_menu_functions_minimal(Name, Name2, name, name2)\
\
ecs_entity_t spawn_menu_##name##_player(ecs_world_t *world, const ecs_entity_t player) {\
    const ecs_entity_t character = zox_get_value(player, CharacterLink)\
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)\
    const int2 canvas_size = zox_get_value(canvas, PixelSize)\
    SpawnWindowUsers data = get_default_spawn_window_users_data(character, canvas, canvas_size);\
    data.header_zext.text = #Name;\
    data.window.prefab = prefab_menu_##name;\
    data.icon.prefab = prefab_icon_##name2;\
    data.window.user_links_id = zox_id(Name2##Links);\
    return spawn_window_users(world, &data);\
}

// Ex: zox_user_menu_functions(Skills, Skill, skills, skill)

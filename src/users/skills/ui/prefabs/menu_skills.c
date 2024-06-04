ecs_entity_t spawn_prefab_menu_skills(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_menu_skills")
    zox_add_tag(e, MenuSkills)
    return e;
}

ecs_entity_t spawn_menu_skills_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    SpawnWindowUsers data = get_default_spawn_window_users_data(character, canvas, canvas_size);
    data.window.prefab = prefab_menu_stats;
    data.window.user_links_id = zox_id(SkillLinks);
    data.header_zext.text = "Skills";
    data.icon.prefab = prefab_icon_skill;
    return spawn_window_users(world, &data);
}

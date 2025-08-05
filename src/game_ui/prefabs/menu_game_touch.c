// #define spawn_actions_on_touch_menu

// todo: From actions UI, add to menu_game_touch - need prefabs with children
#ifdef spawn_actions_on_touch_menu
    extern void button_event_switch_action(ecs_world_t *world, const ClickEventData *event);
#endif
extern void button_event_jump(ecs_world_t *world, const ClickEventData *event);
extern void button_event_attack(ecs_world_t *world, const ClickEventData *event);

ecs_entity_t spawn_prefab_menu_game_touch(
    ecs_world_t *world,
    const ecs_entity_t prefab
) {
    zox_prefab_child(prefab)
    zox_prefab_name("menu_game_touch")
    zox_add_tag(e, MenuGameTouch)
    zox_prefab_set(e, AnchorSize, { float2_one })
    zox_prefab_set(e, Children, { 0, NULL });
    return e;
}
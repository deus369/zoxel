typedef struct {
    ecs_entity_t clicker;
    ecs_entity_t clicked;
} ClickEventData;
zox_function_component(ClickEvent, void, ecs_world_t*, const ClickEventData*)
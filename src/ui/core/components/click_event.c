typedef struct {
    entity clicker;
    entity clicked;
} ClickEventData;
zox_function_component(ClickEvent, void, ecs*, const ClickEventData*)
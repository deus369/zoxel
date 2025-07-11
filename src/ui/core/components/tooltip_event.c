typedef struct  {
    byte event;
    ecs_entity_t tooltip;
    ecs_entity_t data;
    ecs_entity_t triggered;
} TooltipEventData;
zox_function_component(TooltipEvent, byte, ecs_world_t*, const TooltipEventData*)
typedef struct  {
    byte event;
    entity tooltip;
    entity data;
    entity triggered;
} TooltipEventData;
zox_function_component(TooltipEvent, byte, ecs*, const TooltipEventData*)
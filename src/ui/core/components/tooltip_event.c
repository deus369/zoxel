typedef struct  {
    byte event;
    entity tooltip;
    entity data;
    entity triggered;
} TooltipEventData;
zoxc_function(TooltipEvent, byte, ecs*, const TooltipEventData*);
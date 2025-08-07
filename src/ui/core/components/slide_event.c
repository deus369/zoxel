typedef struct {
    entity dragged;
    entity player;
    float value;    // slider value passed through event
} SlideEventData;
zox_function_component(SlideEvent, void, ecs*, const SlideEventData*)
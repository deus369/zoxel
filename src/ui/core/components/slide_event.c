typedef struct {
    ecs_entity_t dragged;
    ecs_entity_t player;
    float value;    // slider value passed through event
} SlideEventData;
zox_function_component(SlideEvent, void, ecs_world_t*, const SlideEventData*)
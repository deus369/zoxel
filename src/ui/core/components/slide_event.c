typedef struct {
    entity dragged;
    entity player;
    float value;    // slider value passed through event
} SlideEventData;
zoxc_function(SlideEvent, void, ecs*, const SlideEventData*);
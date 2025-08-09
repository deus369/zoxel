typedef struct {
    entity clicker;
    entity clicked;
} ClickEventData;
zoxc_function(ClickEvent, void, ecs*, const ClickEventData*);
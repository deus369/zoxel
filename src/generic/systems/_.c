#include "destroy_in_frame_system.c"
#include "generic_event_debug_system.c"
#include "timed_event_system.c"

void define_systems_generic(ecs_world_t *world) {
    zox_system(DestroyInFrameSystem, EcsOnStore, [none] DestroyInFrame)
    zox_system_1(TimedEventSystem, EcsPreStore, [in] TimedEvent, [in] generic.EventInput, [out] EventTime)
}
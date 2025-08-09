zoxc_byte(TriggerActionA);
zoxc_byte(TriggerActionB);

void define_components_triggers(ecs_world_t *world) {
    zox_define_component_byte(TriggerActionA);
    zox_define_component_byte(TriggerActionB);
}
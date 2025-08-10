zox_tag(Npc);
zox_tag(Jumper);
zox_tag(Wanderer);
zox_tag(Coward);
zoxc_byte(Behaviour);
zoxc_byte(DefaultBehaviour);
zoxc_byte(MoveForwards);
zoxc_byte(RotateTowards);
zoxc_float(MoveSpeed);
zoxc_float3(TargetPosition);
zoxc_float3(ThreatPosition);
zoxc_float3(WanderDirection);

void define_components_npcs(ecs* world) {
    zox_define_tag(Npc);
    zox_define_tag(Jumper);
    zox_define_tag(Wanderer);
    zox_define_tag(Coward);
    zoxd_byte(Behaviour);
    zoxd_byte(DefaultBehaviour);
    zoxd_byte(MoveForwards);
    zoxd_byte(RotateTowards);
    zox_define_component_float(MoveSpeed);
    zox_define_component_float3(TargetPosition);
    zox_define_component_float3(ThreatPosition);
    zox_define_component_float3(WanderDirection);
}
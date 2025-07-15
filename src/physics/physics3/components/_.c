zox_component_byte(InitializePhysics3D)
zox_component_float3(Velocity3D)
zox_component_float3(Acceleration3D)
zox_component_float4(Omega3D)
zox_component_float4(Alpha3D)
zox_component_byte(Grounded) // use for friction - todo: use bit operations to check what sides cause friction and apply like that
// move to new sub module - Forces
zox_component_float3(Gravity3D)
zox_component_byte(Flying)
zox_declare_tag(Jumper)
zox_component_double(Jump)

void zox_define_components_physics3(ecs_world_t *world) {
    zox_define_tag(Jumper)
    zox_define_component_byte(InitializePhysics3D)
    zox_define_component_float3(Velocity3D)
    zox_define_component_float3(Acceleration3D)
    zox_define_component_float4(Omega3D)
    zox_define_component_float4(Alpha3D)
    zox_define_component_byte(Grounded)
    zox_define_component_byte(Jump)
    zox_define_component_float3(Gravity3D)
}
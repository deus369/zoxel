zoxc_byte(InitializePhysics3D);
zoxc_float3(Velocity3D);
zoxc_float3(Acceleration3D);
zoxc_float3(Omega3D);
zoxc_float3(Alpha3D);
// move to new sub module - Forces
zoxc_float3(Gravity3D);
zoxc_byte(Flying);
zoxc_float3(LastPosition3D);
zoxc_float3(LastUnstuck3);

void zox_define_components_physics3(ecs *world) {
    zox_define_component_byte(InitializePhysics3D);
    zox_define_component_float3(Velocity3D);
    zox_define_component_float3(Acceleration3D);
    zox_define_component_float3(Omega3D);
    zox_define_component_float3(Alpha3D);
    zox_define_component_float3(Gravity3D);
    zox_define_component_float3(LastPosition3D);
    zox_define_component_float3(LastUnstuck3);
}
zox_tag(EulerOverride);
zox_tag(CameraTransform);
zoxc_float3(Position3D);
zoxc_float4(Rotation3D);     // A quaternion rotation
zoxc_float3(Scale3D);          // A Non Uniform 3D Scale
zoxc(Matrix, float4x4);       // A matrix used for rendering
zoxc_float3(Euler);          // A rotation but kept in euler form
zoxc_float2(EulerLimitX);    // a limitation of euler x axis
zoxc_float2(EulerLimitZ);    // a limitation of euler z axis
zoxc_float3(LocalPosition3D);
zoxc_float4(LocalRotation3D);
zoxc(TransformMatrix, float4x4);

void define_components_transforms3(ecs* world) {
    zox_define_tag(EulerOverride);
    zox_define_tag(CameraTransform);
    zox_define_component_float3(Position3D);
    zox_define_component_float4(Rotation3D);
    zox_define_component_float3(Scale3D);
    zox_define_component(Matrix);
    zox_define_component_float3(Euler);
    zox_define_component_float2(EulerLimitX);
    zox_define_component_float2(EulerLimitZ);
    zox_define_component_float3(LocalPosition3D);
    zox_define_component_float4(LocalRotation3D);
    zox_define_component(TransformMatrix);
}
zox_tag(Camera);
zox_tag(Camera2D);
zox_tag(Camera3D);
zox_tag(FirstPersonCamera);
zox_tag(CameraUI);
zox_tag(ElementBillboard);
zoxc_byte(CanRoam);
zoxc_byte(CameraMode);
zoxc_byte(CameraViewing);
zoxc_float(FieldOfView);
zoxc_float(CameraNearDistance);
zoxc_entity(CameraLink);
zoxc_entity(CameraTarget);
zoxc_entity(CameraFollowLink);
zoxc_int2(ScreenPosition);
zoxc_float4(ScreenToCanvas);
zoxc(ProjectionMatrix, float4x4);
zoxc(ViewMatrix, float4x4); // todo: rename to ViewProjectionMatrix
zoxc_array(CameraPlanes, plane, 6);
zoxc_array(FrustumCorners, double3, 8); // double3 | float3
// Render Cameras
zox_tag(RenderCamera);
zox_tag(RenderTexture);
zoxc_entity(RenderTextureLink);
zoxc_entity(RenderCameraLink);
zoxc_entities(CameraLinks)

void define_components_cameras(ecs *world) {
    zox_define_tag(Camera);
    zox_define_tag(Camera2D);
    zox_define_tag(Camera3D);
    zox_define_tag(FirstPersonCamera);
    zox_define_tag(CameraUI);
    zox_define_tag(ElementBillboard);
    zox_define_component_byte(CanRoam);
    zox_define_component_byte(CameraMode);
    zox_define_component_byte(CameraViewing);
    zox_define_component_float(FieldOfView);
    zox_define_component_float(CameraNearDistance);
    zox_define_component_int2(ScreenPosition);
    zox_define_component_entity(CameraLink);
    zox_define_component_entity(CameraTarget);
    zox_define_component_entity(CameraFollowLink);
    zox_define_component(ProjectionMatrix);
    zox_define_component(ViewMatrix);
    // zox_define_component(ViewProjectionMatrix)
    zox_define_component_float4(ScreenToCanvas);
    zox_define_component_array(FrustumCorners);
    zox_define_component_array(CameraPlanes);
    // render cameras
    zox_define_tag(RenderCamera);
    zox_define_tag(RenderTexture);
    zox_define_component_entity(RenderTextureLink);
    zox_define_component_entity(RenderCameraLink);
    zox_define_entities_component(CameraLinks);
}
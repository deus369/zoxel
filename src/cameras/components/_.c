zox_declare_tag(Camera)
zox_declare_tag(Camera2D)
zox_declare_tag(Camera3D)
zox_declare_tag(FirstPersonCamera)
zox_declare_tag(CameraUI)
zox_declare_tag(ElementBillboard)
zox_component_byte(CanRoam)
zox_component_byte(CameraMode)
zox_component_byte(CameraViewing)
zox_component_float(FieldOfView)
zox_component_float(CameraNearDistance)
zox_component_entity(CameraLink)
zox_component_entity(CameraTarget)
zox_component_entity(CameraFollowLink)
zox_component_int2(ScreenPosition)
zox_component_float4(ScreenToCanvas)
zox_component(ProjectionMatrix, float4x4)
zox_component(ViewMatrix, float4x4) // todo: rename to ViewProjectionMatrix
// zox_component(ViewProjectionMatrix, float4x4)
//zox_memory_component(FrustumCorners, double3)
//zox_memory_component(CameraPlanes, plane)
zox_component_array(CameraPlanes, plane, 6)
zox_component_array(FrustumCorners, double3, 8)
// Render Cameras
zox_declare_tag(RenderCamera)
zox_declare_tag(RenderTexture)
zox_component_entity(RenderTextureLink)
zox_component_entity(RenderCameraLink)
zox_entities_component(CameraLinks)

void define_components_cameras(ecs_world_t *world) {
    zox_define_tag(Camera)
    zox_define_tag(Camera2D)
    zox_define_tag(Camera3D)
    zox_define_tag(FirstPersonCamera)
    zox_define_tag(CameraUI)
    zox_define_tag(ElementBillboard)
    zox_define_component_byte(CanRoam)
    zox_define_component_byte(CameraMode)
    zox_define_component_byte(CameraViewing)
    zox_define_component_float(FieldOfView)
    zox_define_component_float(CameraNearDistance)
    zox_define_component_int2(ScreenPosition)
    zox_define_component_entity(CameraLink)
    zox_define_component_entity(CameraTarget)
    zox_define_component_entity(CameraFollowLink)
    zox_define_component(ProjectionMatrix)
    zox_define_component(ViewMatrix)
    // zox_define_component(ViewProjectionMatrix)
    zox_define_component_float4(ScreenToCanvas)
    zox_define_component_array(FrustumCorners)
    zox_define_component_array(CameraPlanes)
    // render cameras
    zox_define_tag(RenderCamera)
    zox_define_tag(RenderTexture)
    zox_define_component_entity(RenderTextureLink)
    zox_define_component_entity(RenderCameraLink)
    zox_define_entities_component(CameraLinks)
}
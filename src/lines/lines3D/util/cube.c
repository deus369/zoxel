void add_debug_cube(ecs_world_t *world, const ecs_entity_t e, const float3 size) {
    zox_prefab_set(e, DebugCubeLines, { 1 })
    zox_add_tag(e, CubeLines)
    zox_prefab_set(e, CubeLinesThickness, { 4 })
    zox_prefab_set(e, ColorRGB, {{ 0, 255, 255 }})
    zox_prefab_set(e, Bounds3D, { size })
    zox_prefab_set(e, RenderLod, { 0 })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_add(e, MeshIndicies)
}
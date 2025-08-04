ecs_entity_t spawn_prefab_cube(ecs_world_t *world) {
    zox_prefab()
    // zox_prefab_name("cube")
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, Scale1D, { 1 })
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_prefab_set(e, Brightness, { 0.6f })
    zox_prefab_set(e, MeshDirty, { mesh_state_trigger_slow })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, Scale1D, { 0.125f })
    if (headless) {
        return e;
    }
    zox_add_tag(e, MeshBasic3D)
    zox_prefab_set(e, MeshIndicies, { 0, NULL });
    zox_prefab_set(e, MeshVertices, { 0, NULL });
    zox_prefab_set(e, ShaderLink, { 0 })
    add_gpu_mesh(world, e);
    add_gpu_material(world, e);
    prefab_set_mesh_indicies(world, e, cube2_indicies, cube2_indicies_length);
    prefab_set_mesh_vertices_float3(world, e, cube2_vertices, cube2_vertices_length);
    return e;
}

ecs_entity_t spawn_cube(ecs_world_t *world,
    const ecs_entity_t prefab,
    const float3 position)
{
    zox_instance(prefab)
    // zox_name("cube")
    // zox_add_tag(e, MeshBasic3D)
    zox_set(e, Position3D, { position })
    spawn_gpu_mesh(world, e);
    const uint2 shader = zox_get_value(shader_basic3D, ShaderGPULink)
    const uint material = spawn_gpu_material(world, e, shader);
    const MaterialBasic3D attributes = create_MaterialBasic3D(material);
    zox_set_data(e, MaterialBasic3D, attributes)
    zox_set(e, ShaderLink, { shader_basic3D })
    return e;
}

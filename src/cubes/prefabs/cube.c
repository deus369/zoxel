ecs_entity_t spawn_prefab_cube(ecs_world_t *world) {
    zox_prefab()
    // zox_prefab_name("prefab_cube")
    add_transform3Ds(world, e, 1);
    add_transform_matrix(world, e);
    zox_prefab_set(e, Brightness, { 0.6f })
    zox_prefab_set(e, MeshDirty, { mesh_state_trigger })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, Scale1D, { 0.125f })
    if (headless) {
        return e;
    }
    zox_add_tag(e, MeshBasic3D)
    zox_prefab_add(e, MeshIndicies)
    zox_prefab_add(e, MeshVertices)
    zox_prefab_set(e, ShaderLink, { 0 })
    add_gpu_mesh(world, e);
    add_gpu_material(world, e);
    prefab_set_mesh_indicies(world, e, cube2_indicies, cube2_indicies_length);
    prefab_set_mesh_vertices_float3(world, e, cube2_vertices, cube2_vertices_length);
    return e;
}

ecs_entity_t spawn_cube(ecs_world_t *world, const ecs_entity_t prefab, const float3 position) {
    zox_instance(prefab)
    // zox_name("cube")
    // zox_add_tag(e, MeshBasic3D)
    zox_set(e, Position3D, { position })
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, shader3D);

    /*if (zox_has(material_basic3D, MaterialGPULink)) {
        zox_geter(material_basic3D, MaterialGPULink, material_basic3D_link)
        zox_prefab_set(e, MaterialGPULink, { material_basic3D_link->value })
    } else {
        zox_log("! (%lu) [%s] does not have material gpu link\n", material_basic3D, zox_get_name(material_basic3D))
    }*/

    const GLuint2 shader = zox_get_value(shader_basic3D, ShaderGPULink)
    zox_set(e, ShaderLink, { shader_basic3D })
    spawn_gpu_material(world, e, shader);
    //const MaterialTextured3D attributes = create_MaterialTextured3D(material);
    //zox_set_data(e, MaterialTextured3D, attributes)

    return e;
}

ecs_entity_t spawn_prefab_cube_textured(ecs_world_t *world, const ecs_entity_t prefab) {
    const int2 texture_size = int2_zero; // { 16, 16 };
    // zox_prefab_child(prefab)
    zox_clone(prefab)
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, Brightness, { 1 })
    zox_prefab_set(e, Color, { color_red })
    zox_add_tag(e, Texture)
    zox_prefab_set(e, TextureData, { 0, NULL })
    zox_prefab_set(e, TextureSize, { texture_size })
    zox_prefab_set(e, TextureDirty, { 0 })
    zox_prefab_set(e, Seed, { 666 })
    zox_prefab_set(e, GenerateTexture, { zox_generate_texture_trigger })
    add_noise_texture(world, e);
    if (headless) {
        return e;
    }
    zox_remove_tag(e, MeshBasic3D)
    zox_add_tag(e, TexturedMesh3D)
    zox_prefab_set(e, MaterialTextured3D, { })
    zox_prefab_set(e, UvsGPULink, { 0 })
    zox_prefab_set(e, MeshGPULink, { })
    zox_prefab_set(e, MaterialGPULink, { 0 })
    zox_prefab_set(e, ColorsGPULink, { 0 })
    zox_prefab_add(e, MeshColorRGBs)
    zox_prefab_set(e, TextureGPULink, { 0 })
    prefab_set_mesh_indicies(world, e, cube2_indicies, cube2_indicies_length);
    prefab_set_mesh_vertices_float3(world, e, cube2_vertices, cube2_vertices_length);
    prefab_set_mesh_colors_rgb(world, e, (color_rgb) { 255, 255, 255 }, cube2_vertices_length);
    add_gpu_texture(world, e);
    prefab_set_mesh_uvs_float2(world, e, cube2_uvs, cube2_uvs_length);
    return e;
}

ecs_entity_t spawn_cube_textured(ecs_world_t *world, const ecs_entity_t prefab, const float3 position, const ecs_entity_t texture) {
    const ecs_entity_t e = spawn_cube(world, prefab, position);
    // zox_name("cube_textured")
    clone_texture_entity_to_entity(world, e, texture);
    if (headless || !shader_textured3D) {
        return e;
    }
    // zox_log("+ spawned cubet\n")
    spawn_gpu_mesh(world, e);
    spawn_gpu_uvs(world, e);
    spawn_gpu_colors(world, e);
    spawn_gpu_texture(world, e);
    const GLuint2 shader = zox_get_value(shader_textured3D, ShaderGPULink)
    const GLuint material = spawn_gpu_material(world, e, shader);
    const MaterialTextured3D attributes = create_MaterialTextured3D(material);
    zox_set_data(e, MaterialTextured3D, attributes)
    zox_set(e, ShaderLink, { shader_textured3D })
    return e;
}

// adds texture generated
extern void prefab_add_texture_generated(ecs_world_t *world, ecs_entity_t e, int2 textureSize, unsigned char generate);
// zox_render3D_system(TexturedRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] RenderDisabled, [in] MaterialGPULink, [in] TextureGPULink, [in] MaterialTextured3D, [none] TexturedMesh3D)
// zox_system_1(Mesh3DTexturedUploadSystem, zox_pip_mainthread, [in] MeshIndicies, [in] MeshVertices, [in] MeshUVs, [in] MeshColorRGBs, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [out] MeshDirty)

ecs_entity_t spawn_prefab_cube_textured(ecs_world_t *world, const ecs_entity_t prefab) {
    const int2 texture_size = int2_zero; // { 16, 16 };
    zox_prefab_child(prefab)
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_add_tag(e, TexturedMesh3D)
    // mesh
    zox_prefab_set(e, MeshGPULink, { })
    // zox_prefab_set(e, MeshIndicies, { 0 })
    // material
    zox_prefab_set(e, ShaderLink, { 0 })
    zox_prefab_set(e, MaterialGPULink, { 0 })
    zox_prefab_set(e, MaterialTextured3D, { })
    // set colors
    zox_prefab_set(e, ColorsGPULink, { 0 })
    zox_prefab_set(e, Brightness, { 1 })
    prefab_set_mesh_uvs_float2(world, e, cube_uvs, cube_uvs_length);
    // prefab_set_mesh_uvs_float(world, e, cube_uvs_singles, cube_uvs_singles_length);
    zox_prefab_add(e, MeshColorRGBs)
    // prefab_set_mesh_colors_rgb(world, e, (color_rgb) { 255, 255, 255 }, cube_vertices_length);
    prefab_set_mesh_colors_rgb(world, e, (color_rgb) { 255, 255, 255 }, cube_vertices_length);
    // uvs
    zox_prefab_set(e, UvsGPULink, { 0 })
    // texture
    zox_prefab_set(e, Color, { color_red })
    zox_prefab_set(e, TextureGPULink, { 0 })
    prefab_add_texture_generated(world, e, texture_size, zox_generate_texture_trigger);
    add_noise_texture(world, e);
    add_gpu_texture(world, e);
    return e;
}

ecs_entity_t spawn_cube_textured(ecs_world_t *world, const ecs_entity_t prefab, const float3 position) {
    const ecs_entity_t e = spawn_cube(world, prefab, position);
    // zox_name("cube_textured")
    clone_texture_to_entity(world, e, "dark_block");
    if (!headless && shader_textured3D) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_uvs(world, e);
        spawn_gpu_colors(world, e);
        spawn_gpu_texture(world, e);
        const GLuint2 shader = zox_get_value(shader_textured3D, ShaderGPULink)
        const GLuint material = spawn_gpu_material(world, e, shader);
        const MaterialTextured3D attributes = create_MaterialTextured3D(material);
        zox_set_data(e, MaterialTextured3D, attributes)
        zox_set(e, ShaderLink, { shader_textured3D })
    }
    return e;
}

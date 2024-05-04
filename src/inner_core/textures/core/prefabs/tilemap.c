ecs_entity_t prefab_tilemap;

ecs_entity_t spawn_prefab_tilemap(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_tilemap")
    zox_add_tag(e, Tilemap)
    zox_prefab_set(e, TilemapSize, { { 1, 1 } })
    zox_prefab_set(e, TextureLinks, { 0, NULL })
    zox_prefab_set(e, TilemapUVs, { 0, NULL })
    add_texture(world, e, int2_zero, 1);
    if (!headless) {
        add_gpu_texture(world, e);
        add_gpu_material(world, e);
        add_gpu_texture(world, e);
    }
    prefab_tilemap = e;
    return e;
}

ecs_entity_t spawn_tilemap(ecs_world_t *world) {
    zox_instance(prefab_tilemap)
    zox_name("tilemap")
    // zox_set(e, TextureSize, { texture_size })
    if (!headless) {
        zox_set(e, ShaderLink, { shader_textured3D })
        const GLuint2 shader = zox_get_value(shader_textured3D, ShaderGPULink)
        const GLuint material = spawn_gpu_material(world, e, shader);
        spawn_gpu_texture(world, e);
        const MaterialTextured3D attributes = create_MaterialTextured3D(material);
        zox_set_data(e, MaterialTextured3D, attributes)
    }
    return e;
}

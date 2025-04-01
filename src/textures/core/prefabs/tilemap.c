ecs_entity_t spawn_prefab_tilemap(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_tilemap")
    zox_add_tag(e, Tilemap)
    zox_prefab_set(e, RealmLink, { 0 })
    zox_prefab_set(e, TilemapSize, { { 1, 1 } })
    prefab_add_texture_generated(world, e, int2_zero, zox_generate_texture_none);
    if (!headless) {
        add_gpu_texture(world, e);
        add_gpu_material(world, e);
    }
    zox_prefab_set(e, TextureLinks, { 0, NULL })
    zox_prefab_set(e, TilemapUVs, { 0, NULL })
    return e;
}

ecs_entity_t spawn_tilemap(ecs_world_t *world, ecs_entity_t prefab) {
#ifdef zox_disable_tilemaps
    return 0;
#endif
    if (prefab == 0) return 0;
    zox_instance(prefab)
    zox_name("tilemap")
    if (!headless && shader_textured3D) {
        spawn_gpu_texture(world, e);
        const GLuint2 shader = zox_get_value(shader_textured3D, ShaderGPULink)
        const GLuint material = spawn_gpu_material(world, e, shader);
        const MaterialTextured3D attributes = create_MaterialTextured3D(material);
        zox_set(e, ShaderLink, { shader_textured3D })
        // zox_set(e, MaterialGPULink, { material })
        zox_set_data(e, MaterialTextured3D, attributes)
    }
    return e;
}

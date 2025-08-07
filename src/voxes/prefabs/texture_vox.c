entity spawn_prefab_vox_texture(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("vox_texture")
    zox_add_tag(e, VoxTexture)
    zox_prefab_add(e, VoxLink)
    zox_prefab_add(e, VoxBakeSide)
    zox_prefab_set(e, GenerateTexture, { zox_generate_texture_trigger })
    return e;
}
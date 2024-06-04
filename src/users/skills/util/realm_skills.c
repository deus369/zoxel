ecs_entity_t meta_item_aura;

void spawn_realm_skills(ecs_world_t *world, const ecs_entity_t realm) {
    SkillLinks *items = zox_get_mut(realm, SkillLinks)
    resize_memory_component(SkillLinks, items, ecs_entity_t, 1)

    meta_item_aura = spawn_meta_skill(world, "aura");
    zox_set(meta_item_aura, TextureLink, { files_textures[11] });
    items->value[0] = meta_item_aura;

    zox_modified(realm, SkillLinks)
}

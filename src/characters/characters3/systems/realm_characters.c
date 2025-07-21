void spawn_realm_characters(ecs_world_t *world, ecs_entity_t e) {
    if (!zox_has(e, CharacterLinks)) {
        zox_log_error("realm does not have CharacterLinks [%lu]", e)
        return;
    }
    // zox_get_muter(realm, StatLinks, stats)
    zox_geter(e, CharacterLinks, old)
    if (old) {
        // clear previous
        for (int i = 0; i < old->length; i++) {
            const ecs_entity_t e2 = old->value[i];
            if (zox_valid(e2)) {
                zox_delete(e2)
            }
        }
    }
    // zox_log("+ spawning realm characters")
    CharacterLinks characters = (CharacterLinks) { 0, NULL };
    byte chance_max = 0;
    int count = 6; // count of below array
    char* vox_names[] = { "mrpenguin", "slime", "bob", "chicken", "tall_cube", "bigmrpenguin" };
    byte chances[] = { 5, 30, 8, 40, 5, 3 };
    for (int i = 0; i < count; i++) {
        const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data(vox_names[i]));
        if (zox_valid(vox)) {
            // can choose here properties for spawning
            byte chance = chances[i];
            const ecs_entity_t e2 = spawn_character3_meta(world,
                prefab_character3_meta,
                vox,
                chance);
            add_to_CharacterLinks(&characters, e2);
            chance_max += chance;
        }
    }
    zox_set(e, CharactersChanceMax, { chance_max })
    zox_set_ptr(e, CharacterLinks, characters)
}
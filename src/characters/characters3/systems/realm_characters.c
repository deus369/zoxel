extern entity prefab_character3_npc;
extern entity prefab_character3_instanced_npc;
extern entity prefab_character3_skeleton_npc;

void spawn_realm_characters(ecs *world, entity e) {
    if (!zox_valid(e)) {
        return;
    }
    if (!zox_has(e, CharacterLinks)) {
        zox_log_error("realm does not have CharacterLinks [%s]", zox_get_name(e))
        return;
    }
    // zox_get_muter(e, StatLinks, stats)
    zox_geter(e, CharacterLinks, old)
    if (old) {
        // clear previous
        for (int i = 0; i < old->length; i++) {
            const entity e2 = old->value[i];
            if (zox_valid(e2)) {
                zox_delete(e2)
            }
        }
    }
    // zox_log("+ spawning realm characters")
    byte chance_max = 0;
    zox_geter(e, ModelLinks, models);
    CharacterLinks characters = (CharacterLinks) { 0, NULL };

    // add files
    int count = 5; // count of below array
    char* vox_names[] = { "slime", "chicken", "mrpenguin", "bob", "bigmrpenguin" };
    byte chances[] = { 30, 30, 8, 8, 3 };

    entity prefab_character = is_characters_instanced ? prefab_character3_instanced_npc : prefab_character3_npc;

    for (int i = 0; i < count; i++) {
        entity model = string_hashmap_get(files_hashmap_voxes, new_string_data(vox_names[i]));
        if (zox_valid(model)) {
            // can choose here properties for spawning
            byte chance = chances[i];
            const entity e2 = spawn_character3_meta(world,
                prefab_character3_meta,
                prefab_character,
                model,
                chance);
            add_to_CharacterLinks(&characters, e2);
            chance_max += chance;
        }
    }

    // add model links with tag ModelCharacter
    for (int i = 0; i < models->length; i++) {
        const entity model = models->value[i];
        if (!zox_valid(model)) {
            zox_log_error("realm has invalid model [%i]", i)
            continue;
        }
        if (!zox_has(model, ModelCharacter)) {
            continue;
        }
        byte chance = 8;
        const entity e2 = spawn_character3_meta(world,
            prefab_character3_meta,
            prefab_character,
            model,
            chance);
        add_to_CharacterLinks(&characters, e2);
        chance_max += chance;
    }

    // add our skeleton prefab
    {
        byte chance = 5;
        char* svox_name = "grazor";
        entity model = string_hashmap_get(files_hashmap_voxes, new_string_data(svox_name));
        const entity e2 = spawn_character3_meta(world,
            prefab_character3_meta,
            prefab_character3_skeleton_npc,
            model,
            chance);
        add_to_CharacterLinks(&characters, e2);
        chance_max += chance;
    }

    zox_set(e, CharactersChanceMax, { chance_max })
    zox_set_ptr(e, CharacterLinks, characters)
    zox_logv("At [%f] Realm [characters] [%i] spawned.", zox_current_time, characters.length);
}
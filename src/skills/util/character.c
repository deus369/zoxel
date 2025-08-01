const int character_skills_count = 8; // having blank items seems to b reak it

// todo: take in npc spawn meta data, like location, biome, etc
void spawn_character_skills(ecs_world_t *world, spawned_character3D_data *data) {
    if (!data->p) {
        return;
    }
    int skills_count = character_skills_count;
    if (test_all_skills && data->p) {
        skills_count = 16;
    }
    SkillLinks *skills = &((SkillLinks) { 0, NULL });
    initialize_SkillLinks(skills, skills_count);
    if (!skills->value) {
        zox_log(" ! failed allocating memory for skills\n")
        return;
    }
    for (int i = 0; i < skills->length; i++) {
        skills->value[i] = 0; // blanks are item slots
    }

    int place_index = 0;
    if (test_all_skills && data->p) {
        // get voxels
        zox_geter(data->p, GameLink, gameLink)
        zox_geter(gameLink->value, RealmLink, realmLink)
        zox_geter(realmLink->value, SkillLinks, realm_skills)
        for (int i = 0; i < realm_skills->length; i++) {
            if (i >= skills->length) {
                break;
            }
            const ecs_entity_t skill = realm_skills->value[i];
            if (!zox_valid(skill)) {
                zox_log_error("skill invalid [%i]", i)
                continue;
            }
            skills->value[place_index++] = spawn_user_skill(world, skill, data->e);
        }
    }

    zox_set(data->e, SkillLinks, { skills->length, skills->value })
}

    /*if (meta_skill_aura_life) {
        skills->value[0] = spawn_user_skill(world, meta_skill_aura_life, data->e);
    }
    if (meta_skill_aura_death) {
        skills->value[1] = spawn_user_skill(world, meta_skill_aura_death, data->e);
    }
    if (meta_skill_aura_fire) {
        skills->value[2] = spawn_user_skill(world, meta_skill_aura_fire, data->e);
    }*/

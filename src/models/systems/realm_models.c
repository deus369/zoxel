void spawn_realm_models(ecs_world_t *world, const ecs_entity_t e) {
    if (!zox_valid(e)) {
        return;
    }
    if (!zox_has(e, ModelLinks)) {
        zox_log_error("realm does not have ModelLinks [%lu]", e)
        return;
    }

    // get realms colors
    zox_geter(e, Colors, realm_colors);
    color grass_color;
    if (realm_colors->length < 5 || grayscale_mode) {
        zox_log("+ grayscale_mode enabled")
        grass_color = color_grayscale(144);
    } else {
        grass_color = realm_colors->value[2];
    }

    zox_geter(e, ModelLinks, old)
    if (old) {
        for (int i = 0; i < old->length; i++) {
            zox_delete(old->value[i])
        }
        dispose_ModelLinks_const(old);
    }

    ModelLinks models = (ModelLinks) { 0, NULL };

    // models
    // grass - contains a bunch of variants
    // todo: set different heights
    {
        zox_neww(e2)
        zox_set_unique_name(e2, "model_group_grass")

        ModelLinks variants = (ModelLinks) { 0, NULL };
        for (int i = 0; i < grass_variants; i++) {
            ecs_entity_t model = spawn_model_grass(world, grass_color, 666 * i);
            add_to_ModelLinks(&variants, model);
        }
        zox_set_ptr(e2, ModelLinks, variants)

        add_to_ModelLinks(&models, e2);
    }

    // spawn slime like npc
    {
        zox_neww(e2)
        zox_set_unique_name(e2, "model_group_slem")
        zox_add_tag(e2, ModelCharacter)

        ModelLinks variants = (ModelLinks) { 0, NULL };
        for (int i = 0; i < grass_variants; i++) {
            ecs_entity_t model = spawn_model_grass(world,
                (color) { grass_color.g, grass_color.b, grass_color.r, grass_color.a },
                2666 * i);
            add_to_ModelLinks(&variants, model);
        }
        zox_set_ptr(e2, ModelLinks, variants)

        add_to_ModelLinks(&models, e2);
    }

    zox_set_ptr(e, ModelLinks, models)

    zox_logv("At [%f] Realm [models] [%i] spawned.", zox_current_time, models.length);
}
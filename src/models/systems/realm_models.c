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
        zox_log_error("realm colors not found")
        grass_color = color_grayscale(144);
    } else {
        grass_color = realm_colors->value[2];
    }

    zox_geter(e, ModelLinks, old)
    if (old) {
        for (int i = 0; i < old->length; i++) {
            zox_delete(old->value[i])
        }
        free(old->value);
    }

    ModelLinks models = (ModelLinks) { 0, NULL };

    // models
    // grass - contains a bunch of variants
    // todo: set different heights
    {
        zox_neww(grass)
        zox_set_unique_name(grass, "model_group_grass")
        ModelLinks grass_models = (ModelLinks) { 0, NULL };
        for (int i = 0; i < grass_variants; i++) {
            ecs_entity_t var1 = spawn_model_grass(world, grass_color, 666 * i);
            add_to_ModelLinks(&grass_models, var1);
        }
        zox_set_ptr(grass, ModelLinks, grass_models)
        add_to_ModelLinks(&models, grass);
    }

    zox_set_ptr(e, ModelLinks, models)
}
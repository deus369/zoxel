const unsigned char realm_voxels = 5;
ecs_entity_t prefab_realm;
ecs_entity_t local_realm;

ecs_entity_t spawn_prefab_realm(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_realm")
    zox_add_tag(e, Realm);
    zox_prefab_set(e, Colors, { 0, NULL })
    zox_prefab_set(e, VoxelLinks, { 0, NULL })
    prefab_realm = e;
    return e;
}

ecs_entity_t spawn_realm(ecs_world_t *world) {
    zox_instance(prefab_realm)
    zox_name("realm")
    // VoxelLinks *voxelLinks = zox_get_mut(e, VoxelLinks)
    zox_get_mutt(e, VoxelLinks, voxelLinks)
    resize_memory_component(VoxelLinks, voxelLinks, ecs_entity_t, realm_voxels)
    // dirt color - hsv - hue saturation value
    const float max_value = 70;
    const float min_value = 30;
    const float max_saturation = 50;
    const float min_saturation = 24;
    float3 soil_hsv = (float3) { 360.0f * (rand() % 100) * 0.01f, min_saturation + (max_saturation - min_saturation) * (rand() % 100) * 0.01f, min_value + (max_value - min_value) * (rand() % 100) * 0.01f };
    float3 grass_hsv = (float3) { 360.0f - soil_hsv.x, soil_hsv.y, soil_hsv.z };
    if (hsv_to_color(grass_hsv).r > hsv_to_color(soil_hsv).r)
    {
        float soil_hue = soil_hsv.x;
        soil_hsv.x = grass_hsv.x;
        grass_hsv.x = soil_hue;
        zox_log(" > grass red was greater, swapping hues\n")
    }
    const color soil_color = hsv_to_color(soil_hsv);
    const color grass_color = hsv_to_color(grass_hsv);
    zox_log(" + soil hsv: %fx%fx%f\n", soil_hsv.x, soil_hsv.y, soil_hsv.z)
    zox_log(" + soil color: %ix%ix%i\n", soil_color.r, soil_color.g, soil_color.b)
    zox_log(" + grass_hsv: %fx%fx%f\n", grass_hsv.x, grass_hsv.y, grass_hsv.z)
    zox_log(" + grass_color: %ix%ix%i\n", grass_color.r, grass_color.g, grass_color.b)
    for (unsigned char i = 0; i < voxelLinks->length; i++) {
        if (i == 0) voxelLinks->value[i] = spawn_voxel(world, i, soil_color);
        else if (i == 1) voxelLinks->value[i] = spawn_voxel(world, i, grass_color);
        else {
            const unsigned char color_margin = 32;
            const color voxel_color = (color) { color_margin + rand() % (255 - color_margin * 2), color_margin + rand() % (255 - color_margin * 2), color_margin + rand() % (255 - color_margin * 2), 255 };
            voxelLinks->value[i] = spawn_voxel(world, i, voxel_color);
        }
    }
    zox_modified(e, VoxelLinks)
    local_realm = e;
    return e;
}

void add_to_labels_textures(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level) {
    if (!(e && zox_has(e, Textures))) return;
    tree_level++;
    const Textures *component = zox_get(e, Textures)
    for (int i = 0; i < component->length; i++) {
        ecs_entity_t texture = component->value[i];
        add_entity_to_labels(world, texture, labels, entities, tree_level);
        // add_entity_children_to_labels(world, component->value[i], labels, entities, tree_level);
    }
}

void add_to_labels_voxel_links(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level) {
    if (!(e && zox_has(e, VoxelLinks))) return;
    tree_level++;
    const VoxelLinks *component = zox_get(e, VoxelLinks)
    for (int i = 0; i < component->length; i++) {
        ecs_entity_t voxel = component->value[i];
        add_entity_to_labels(world, voxel, labels, entities, tree_level);
        add_to_labels_textures(world, voxel, labels, entities, tree_level);
    }
}

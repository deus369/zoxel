ecs_entity_t spawn_prefab_icon_frame_user(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame_user")
    // zox_add_tag(e, UserIconFrame)
    zox_prefab_add(e, UserDataLink)
    zox_prefab_add(e, TooltipEvent)
    return e;
}

void set_icon_label_from_user_data_quantity(ecs_world_t *world, const ecs_entity_t frame, const unsigned char quantity) {
    if (!zox_has(frame, IconLabel)) return;
    if (!zox_has(frame, Children)) {
        zox_log(" ! frame has no children :( %lu\n", frame)
    } else {
        const Children *children = zox_get(frame, Children)
        if (children->length < 2) return;
        const ecs_entity_t zext = children->value[1];
        if (quantity > 1) {
            char text[6];
            sprintf(text, "x%"PRIu64"", quantity);
            set_entity_with_text(world, zext, text);
        } else {
            set_entity_with_text(world, zext, "");
        }
    }
}

void set_icon_label_from_user_data(ecs_world_t *world, const ecs_entity_t frame, const ecs_entity_t data) {
    if (!zox_has(frame, IconLabel)) return;
    if (!zox_has(frame, Children)) {
        zox_log(" ! frame has no children :( %lu\n", frame)
    } else {
        const Children *children = zox_get(frame, Children)
        if (children->length < 2) return;
        const ecs_entity_t zext = children->value[1];
        if (zox_has(data, Quantity)) {
            const unsigned char quantity = zox_get_value(data, Quantity)
            // zox_log("x%i\n", quantity)
            if (quantity > 1) {
                char text[6];
                sprintf(text, "x%"PRIu64"", quantity);
                set_entity_with_text(world, zext, text);
                // zox_log("x%i\n", quantity)
            } else {
                set_entity_with_text(world, zext, "");
            }
        } else {
            set_entity_with_text(world, zext, "");
        }
    }
}

void set_icon_label_from_user_data_direct(ecs_world_t *world, const ecs_entity_t zext, const ecs_entity_t data) {
    if (!zext) return;
    if (zox_has(data, Quantity)) {
        const unsigned char quantity = zox_get_value(data, Quantity)
        // zox_log("x%i\n", quantity)
        if (quantity > 1) {
            char text[6];
            sprintf(text, "x%"PRIu64"", quantity);
            set_entity_with_text(world, zext, text);
            // zox_log("x%i\n", quantity)
        } else {
            set_entity_with_text(world, zext, "");
        }
    } else {
        set_entity_with_text(world, zext, "");
    }
}

void set_icon_from_user_data(ecs_world_t *world, const ecs_entity_t frame, const ecs_entity_t e, const ecs_entity_t data) {
    zox_set(e, UserDataLink, { data })
    if (!data) {
        clear_texture_data(world, e);
        zox_set(e, GenerateTexture, { zox_generate_texture_trigger })
        zox_set(e, TextureSize, { int2_single(default_icon_texture_size) })
        return;
    }
    if (!zox_has(data, TextureLink)) {
        zox_log(" ! issue with data texture [%s] ? %i\n", zox_get_name(data), zox_has(data, TextureLink))
        return;
    }
    const ecs_entity_t texture = zox_get_value(data, TextureLink)
    if (!texture) {
        clear_texture_data(world, e);
        zox_set(e, GenerateTexture, { zox_generate_texture_trigger })
        zox_set(e, TextureSize, { int2_single(default_icon_texture_size) })
        zox_log(" ! texture is invalid from [%s]\n", zox_get_name(data))
        return;
    }
    zox_set(e, GenerateTexture, { zox_generate_texture_none })
    clone_texture_data(world, e, texture);
    zox_set(e, TextureDirty, { 1 })
}

ecs_entity_2 spawn_icon_frame_user(ecs_world_t *world, SpawnIconFrame *data, const ecs_entity_t userdata) {
    const ecs_entity_3 e = spawn_icon_frame(world, data);
    // if prefab has label tag, spawn icon label (Quantity)
    set_icon_from_user_data(world, e.x, e.y, userdata);
    set_icon_label_from_user_data_direct(world, e.z, userdata);
    return (ecs_entity_2) { e.x, e.y };
}

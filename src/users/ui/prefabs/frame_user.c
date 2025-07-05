ecs_entity_t spawn_prefab_frame_user(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_frame_user")
    zox_prefab_set(e, UserDataLink, { 0 })
    zox_prefab_add(e, TooltipEvent)
    return e;
}

void set_icon_label_from_user_data_quantity(ecs_world_t *world, const ecs_entity_t frame, const byte quantity) {
    if (!zox_has(frame, IconLabel)) {
        return;
    }
    if (!zox_has(frame, Children)) {
        zox_log(" ! frame has no children :( %lu\n", frame)
    } else {
        const Children *children = zox_get(frame, Children)
        if (children->length < 2) {
            return;
        }
        const ecs_entity_t zext = children->value[1];
        if (quantity > 1) {
            char text[6];
            // sprintf(text, "x%"PRIu64"", quantity);
            sprintf(text, "x%i", quantity);
            set_entity_text(world, zext, text);
        } else {
            set_entity_text(world, zext, "");
        }
    }
}

void set_icon_label_from_user_data(ecs_world_t *world, const ecs_entity_t frame, const ecs_entity_t data) {
    if (!zox_has(frame, IconLabel)) {
        return;
    }
    if (!zox_has(frame, Children)) {
        zox_log(" ! frame has no children :( %lu\n", frame)
    } else {
        const Children *children = zox_get(frame, Children)
        if (children->length < 2) {
            return;
        }
        const ecs_entity_t zext = children->value[1];
        if (zox_has(data, Quantity)) {
            const byte quantity = zox_get_value(data, Quantity)
            // zox_log("x%i\n", quantity)
            if (quantity > 1) {
                char text[6];
                // sprintf(text, "x%"PRIu64"", quantity);
                sprintf(text, "x%i", quantity);
                set_entity_text(world, zext, text);
                // zox_log("x%i\n", quantity)
            } else {
                set_entity_text(world, zext, "");
            }
        } else {
            set_entity_text(world, zext, "");
        }
    }
}

void set_icon_label_from_user_data_direct(ecs_world_t *world, const ecs_entity_t zext, const ecs_entity_t data) {
    if (!zox_valid(zext) || !zox_valid(data)) {
        return;
    }
    if (zox_has(data, Quantity)) {
        const byte quantity = zox_get_value(data, Quantity)
        // zox_log("x%i\n", quantity)
        if (quantity > 1) {
            char text[6];
            // sprintf(text, "x%"PRIu64"", quantity);
            sprintf(text, "x%i", quantity);
            set_entity_text_raw(world, zext, text);
            // zox_log("x%i\n", quantity)
        } else {
        //    set_entity_text(world, zext, "");
        }
    } else {
    //    set_entity_text(world, zext, "");
    }
}

void set_icon_from_user_data(ecs_world_t *world, const ecs_entity_t frame, const ecs_entity_t e, const ecs_entity_t data) {
    zox_set(frame, UserDataLink, { data })
    zox_set(e, UserDataLink, { data })
    if (!data) {
        clear_texture_data(world, e);
        zox_set(e, GenerateTexture, { zox_generate_texture_trigger })
        zox_set(e, TextureSize, { int2_single(default_icon_texture_size) })
        return;
    }
    if (!zox_has(data, TextureLink)) {
        zox_log_error("[%s] has no texture link component: %i", zox_get_name(data), zox_has(data, TextureLink))
        return;
    }
    const ecs_entity_t texture = zox_get_value(data, TextureLink)
    if (!texture) {
        clear_texture_data(world, e);
        zox_set(e, GenerateTexture, { zox_generate_texture_trigger })
        zox_set(e, TextureSize, { int2_single(default_icon_texture_size) })
        zox_log_error("[%s] has no texture", zox_get_name(data))
        return;
    }
    zox_set(e, GenerateTexture, { zox_generate_texture_none })
    clone_texture_data(world, e, texture);
    zox_set(e, TextureDirty, { 1 })
}

ecs_entity_t spawn_frame_user(ecs_world_t *world, SpawnFrame *data, const ecs_entity_t userdata) {
    const ecs_entity_3 e = spawn_frame(world, data);
    set_icon_from_user_data(world, e.x, e.y, userdata);
    set_icon_label_from_user_data_direct(world, e.z, userdata);
    zox_set_unique_name(e.x, "frame_user")
    zox_set_unique_name(e.y, "icon_user")
    zox_set_unique_name(e.z, "icon_label_user")
    return e.x;
}
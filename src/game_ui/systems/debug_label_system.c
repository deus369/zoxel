const double time_update_debug_label_system_rate = 1.0;
const uint max_debug_characters = 4 * 1024;
double time_update_debug_label_system = 0;

void DebugLabelSystem(ecs_iter_t *it) {
    // timer function for label updates
    time_update_debug_label_system += zox_delta_time;
    if (time_update_debug_label_system >= time_update_debug_label_system_rate) {
        time_update_debug_label_system = 0;
    } else {
        return;
    }
    zox_field_world()
    zox_field_in(PlayerLink, playerLinks, 1)
    zox_field_in(DebugLabelData, debugLabelDatas, 2)
    zox_field_out(ZextDirty, zextDirtys, 3)
    zox_field_out(TextData, textDatas, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value) {
            continue;
        }
        zox_field_i(PlayerLink, playerLinks, playerLink)
        const ecs_entity_t player = playerLink->value;
        if (!player) {
            continue;
        }
        zox_field_i(DebugLabelData, debugLabelDatas, debugLabelData)
        zox_field_o(TextData, textDatas, textData)

        uint index = 0;
        const uint size = max_debug_characters;
        char buffer[size];
        index += snprintf(buffer + index, size - index, "%s [v0.0.1]\n", game_name);
        if (debugLabelData->value) {
            debugLabelData->value(world, player, buffer, size, index);
        }
        // now finish it
        if (index == 0) {
            buffer[0] = '\0';
        }
        if (!is_zext(textData, buffer)) {
            set_zext(textData, buffer);
            zextDirty->value = 1;
        }
    }
} zox_declare_system(DebugLabelSystem)
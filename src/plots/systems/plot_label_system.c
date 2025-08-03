void PlotLabelSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ParentLink)
    zox_sys_out(ZextDirty)
    zox_sys_out(TextData)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ParentLink, parentLink)
        zox_sys_o(ZextDirty, zextDirty)
        zox_sys_o(TextData, textData)
        if (zextDirty->value || !parentLink->value) {
            continue;
        }
        if (!zox_has(parentLink->value, PlotMin) || !zox_has(parentLink->value, PlotMax)) {
            zox_log_error("invalid plot");
            continue;
        }
        zox_geter_value(parentLink->value, PlotMin, double, min);
        zox_geter_value(parentLink->value, PlotMax, double, max);
        const byte buffer_size = 128;
        int buffer_index = 0;
        char buffer[buffer_size];
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "Min %.0fms\nMax %.0fms\n", min, max);
        if (!is_zext(textData, buffer)) {
            set_zext(textData, buffer);
            zextDirty->value = 1;
        }
    }
} zox_declare_system(PlotLabelSystem)
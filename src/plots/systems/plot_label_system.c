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
        if (zextDirty->value) {
            continue;
        }
        if (!parentLink->value) {
            continue;
        }
        if (!zox_has(parentLink->value, PlotDataDouble)) {
            zox_log(" > no PlotDataDouble found on parent\n")
            continue;
        }
        const PlotDataDouble *data = zox_get(parentLink->value, PlotDataDouble)
        if (!data->length) {
            continue;
        }
        double delta_time_min = 99999;
        double delta_time_max = -99999;
        for (int j = 0; j < data->length; j++) {
            const double value = data->value[j];
            if (value <= delta_time_min) {
                delta_time_min = value;
            } else if (value >= delta_time_max) {
                delta_time_max = value;
            }
        }
        delta_time_min *= 1000;
        delta_time_max *= 1000;
        // zox_log("min %f - max %f\n", delta_time_min, delta_time_max)
        const byte buffer_size = 64;
        int buffer_index = 0;
        char buffer[buffer_size];
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "min %.0f\nmax %.0f\n", delta_time_min, delta_time_max);
        if (!is_zext(textData, buffer)) {
            set_zext(textData, buffer);
            zextDirty->value = 1;
        }
    }
} zox_declare_system(PlotLabelSystem)
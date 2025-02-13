void PlotLabelSystem(ecs_iter_t *it) {
    zox_field_in(ParentLink, parentLinks, 1)
    zox_field_out(ZextDirty, zextDirtys, 2)
    zox_field_out(ZextData, zextDatas, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value) continue;
        zox_field_i(ParentLink, parentLinks, parentLink)
        if (!parentLink->value) continue;
        if (!zox_has(parentLink->value, PlotDataDouble)) {
            zox_log(" > no PlotDataDouble found on parent\n")
            continue;
        }
        const PlotDataDouble *data = zox_get(parentLink->value, PlotDataDouble)
        if (!data->length) continue;
        zox_field_o(ZextData, zextDatas, zextData)
        double delta_time_min = 99999;
        double delta_time_max = -99999;
        for (int j = 0; j < data->length; j++) {
            const double value = data->value[j];
            if (value <= delta_time_min) delta_time_min = value;
            if (value >= delta_time_max) delta_time_max = value;
        }
        delta_time_min *= 1000;
        delta_time_max *= 1000;
        // zox_log("min %f - max %f\n", delta_time_min, delta_time_max)
        const byte buffer_size = 64;
        int buffer_index = 0;
        char buffer[buffer_size];
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "min %.0f\nmax %.0f\n", delta_time_min, delta_time_max);
        if (!is_zext(zextData, buffer)) {
            set_zext(zextData, buffer);
            zextDirty->value = 1;
        }

    }
} zox_declare_system(PlotLabelSystem)

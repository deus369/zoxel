void add_plot_data_double(ecs_world_t *world, const ecs_entity_t e, const double value) {
    if (!zox_valid(e)) {
        return;
    }
    zox_get_muter(e, PlotDataDouble, data)
    if (data->length == 0) {
        // zox_log("plot data length is 0\n")
        return;
    }
    for (int i = 0; i < data->length - 1; i++) {
        data->value[i] = data->value[i + 1];
    }
    data->value[data->length - 1] = value;
}

void add_plot_data_time(ecs_world_t *world, const double value) {
    add_plot_data_double(world, plot_window_time, value);
}
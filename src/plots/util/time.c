extern ecs_entity_t plot_time;
extern ecs_entity_t plot_time_system;

void add_plot_data_double(ecs_world_t *world,
    const ecs_entity_t e,
    const double value)
{
    if (!zox_valid(e)) {
        return;
    }
    zox_get_muter(e, PlotDataDouble, data)
    if (data->length == 0) {
        return;
    }
    for (int i = 0; i < data->length - 1; i++) {
        data->value[i] = data->value[i + 1];
    }
    data->value[data->length - 1] = value;
}

void add_plot_data_time(ecs_world_t *world, const double value_s) {
    add_plot_data_double(world, plot_time, value_s * 1000);
}

void add_plot_data_time_system(ecs_world_t *world, const double value_ms) {
    add_plot_data_double(world, plot_time_system, value_ms);
}
// sets the lines height based on frame times
// todo: use PlotData
void PlotLineSystem(ecs_iter_t *it) {
    const int graph_plot_height = 100;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ParentLink)
    zox_sys_in(ChildIndex)
    zox_sys_out(LineLocalPosition2D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ParentLink, parentLink)
        zox_sys_i(ChildIndex, childIndex)
        zox_sys_o(LineLocalPosition2D, lineLocalPosition2D)
        if (!parentLink->value || !zox_has(parentLink->value, PlotDataDouble)) {
            zox_log_error("No PlotDataDouble found on parent");
            continue;
        }
        zox_geter(parentLink->value, PlotDataDouble, data)
        zox_geter_value(parentLink->value, PlotMin, double, min)
        zox_geter_value(parentLink->value, PlotMax, double, max)
        zox_geter_value(parentLink->value, PixelSize, int2, parent_size)
        if (childIndex->value >= data->length) {
            zox_log_error("index [%i] out of bounds (len: %i)", childIndex->value, data->length);
            continue;
        }
        double line_max = max;
        if (max - min <= graph_plot_height) {
            // reset max bounds of our ms
            line_max = min + graph_plot_height;
        }
        double value = data->value[childIndex->value];
        value /= line_max;
        lineLocalPosition2D->value.w = (int) (value * parent_size.y);
    }
} zoxd_system(PlotLineSystem)

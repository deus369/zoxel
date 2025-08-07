ecs_entity_t spawn_list(ecs_world_t *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData element_data,
    const SpawnList list_data)
{
    // byte is_scrollbar = list_data.count > list_data.visible_count;

    // zox_log("+ spawning ui list with [%i] elements", list_data.count)
    // zox_log("   - visible_count [%i]", list_data.visible_count)
    // offset by half a height
    // move down by header size
    // position_y -= window_data.header_font_size + window_data.header_padding * 2;
    int element_height = list_data.font_size + list_data.padding.y * 2;
    int position_y = (int) (element_data.size.y / 2);
    position_y += (int) (0.5f * element_height);

    zox_instance(element_data.prefab)
    set_element_spawn_data(world, e, canvas_data, parent_data, &element_data);
    zox_name("list")
    zox_set(e, Color, { list_data.fill })
    zox_set(e, OutlineColor, { list_data.outline })
    // zox_muter(e, Children, children)
    Children children = (Children) { };

    // now spawn elements to fit our window
    ParentSpawnData child_parent_data = {
        .e = e,
        .position = element_data.position_in_canvas,
        .size = element_data.size
    };
    for (int i = 0; i < list_data.count; i++) {
        SpawnListElement child_data = list_data.elements[i];
        ElementSpawnData child_element_data = {
            .prefab = prefab_button,
            .layer = element_data.layer + 1,
            .anchor = float2_half,
            .render_disabled = !(i >= 0 && i < list_data.visible_count),
        };
        /*if (is_scrollbar) {
            child_element_data.position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;
        }*/
        // BUTTONS
        ecs_entity_t child = 0;
        if (child_data.type == 0) {
            position_y -= element_height + list_data.spacing;
            child_element_data.position.y = position_y;
            SpawnTextData child_text_data = {
                .text = child_data.text,
                .font_size = list_data.font_size,
                .padding = list_data.padding,
                .font_resolution = button_font_resolution,
                .font_fill_color = button_font_fill,
                .font_outline_color = button_font_outline,
                .font_thickness = button_font_thickness_fill,
                .font_outline_thickness = button_font_thickness_outline,
            };
            SpawnButtonData child_button_data = {
                .prefab_zext = prefab_zext,
                .fill = button_fill,
                .outline = button_outline,
            };
            child = spawn_button(world,
                canvas_data,
                child_parent_data,
                child_element_data,
                child_text_data,
                child_button_data);
            if (child_data.on_click.value) {
                zox_set(child, ClickEvent, { child_data.on_click.value })
            }
            zox_add_tag(child, ZextLabel)

        } else {
            position_y -= list_data.slider_height + list_data.spacing;
            child_element_data.position.y = position_y;
            // SLIDERS
            child_element_data.prefab = prefab_slider;
            child_element_data.size = (int2) {
                element_data.size.x - list_data.slider_padding,
                list_data.slider_height
            };
            SpawnSliderData list_data = (SpawnSliderData) {
                .name = child_data.text,
                .prefab_handle = prefab_handle,
                .type = zox_slider_type_float,
                .value = child_data.value,
                .bounds = child_data.value_bounds,
                .handle_width = 32,
            };
            const entity2 e2 = spawn_slider(world,
                canvas_data,
                child_parent_data,
                child_element_data,
                list_data);
            if (child_data.on_slide.value) {
                zox_set(e2.y, SlideEvent, { child_data.on_slide.value })
            }
            child = e2.x;
        }
        add_to_Children(&children, child);
    }
    zox_set_ptr(e, Children, children)
    return e;
}
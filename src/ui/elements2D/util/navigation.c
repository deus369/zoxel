void raycaster_select_first_button(ecs *world, const entity raycaster, const entity window) {
    find_child_with_tag(window, Button, element)
    if (!element) return;
    raycaster_select_element(world, raycaster, element);
}

void canvas_select_first_button(ecs *world, const entity raycaster, const entity canvas) {
    find_child_with_tag(canvas, Window, window)
    if (window) raycaster_select_first_button(world, raycaster, window);
}

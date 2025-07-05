const uint safety_checks_floodfill = 16000;

byte texture_does_flood_reach_edge(
    const color* data,
    const int2 size,
    const color air_color,
    const color boundary_color,
    const int x,
    const int y
) {
    int index = int2_array_index((int2) { x, y }, size);
    if (!color_equal(data[index], air_color)) {
        return 0;
    }

    int visited[size.x * size.y];
    memset(visited, 0, sizeof(visited));
    int stack[size.x * size.y * 2 * 4];
    int stack_top = 0;
    stack[stack_top++] = x; // x-coordinate
    stack[stack_top++] = y; // y-coordinate
    // Loop until the stack is empty
    uint checks = 0;
    while (stack_top > 0 && checks < safety_checks_floodfill) {
        // Pop the top pixel from the stack
        int y = stack[--stack_top];
        int x = stack[--stack_top];
        // Check if the pixel is within the texture bounds and hasn't been visited
        index = int2_array_index((int2) { x, y }, size);
        if (x >= 0 && x < size.x && y >= 0 && y < size.y && !visited[index]) {
            visited[index] = 1;
            if (color_equal(data[index], boundary_color) || !color_equal(data[index], air_color)) {
                continue;
            }
            if (x == 0 || x == size.x - 1 || y == 0 || y == size.y - 1) {
                return 1;
            }
            // Push neighboring pixels onto the stack (left, right, up, down)
            stack[stack_top++] = x - 1; // left
            stack[stack_top++] = y;
            stack[stack_top++] = x + 1; // right
            stack[stack_top++] = y;
            stack[stack_top++] = x;     // up
            stack[stack_top++] = y - 1;
            stack[stack_top++] = x;     // down
            stack[stack_top++] = y + 1;
        }
        checks++;
    }
    return 0;
}

void flood_fill_texture(
    color* data,
    const int2 size,
    const color air_color,
    const color boundary_color,
    const color fill_color,
    const int x,
    const int y
) {
    int index = int2_array_index((int2) { x, y }, size);
    if (!color_equal(data[index], air_color)) {
        return;
    }
    int visited[size.x * size.y];
    memset(visited, 0, sizeof(visited));
    int stack[size.x * size.y * 2 * 4];
    int stack_top = 0;
    stack[stack_top++] = x; // x-coordinate
    stack[stack_top++] = y; // y-coordinate
    // Loop until the stack is empty
    uint checks = 0;
    while (stack_top > 0 && checks < safety_checks_floodfill) {
        // Pop the top pixel from the stack
        int y = stack[--stack_top];
        int x = stack[--stack_top];
        // Check if the pixel is within the texture bounds and hasn't been visited
        index = int2_array_index((int2) { x, y }, size);
        if (x >= 0 && x < size.x && y >= 0 && y < size.y && !visited[index]) {
            visited[index] = 1;
            if (color_equal(data[index], boundary_color) ||color_equal(data[index], fill_color)) {
                continue;
            }
            data[index] = fill_color;
            // zox_log("filling [%ix%i]\n", x, y)
            // Push neighboring pixels onto the stack (left, right, up, down)
            stack[stack_top++] = x - 1; // left
            stack[stack_top++] = y;
            stack[stack_top++] = x + 1; // right
            stack[stack_top++] = y;
            stack[stack_top++] = x;     // up
            stack[stack_top++] = y - 1;
            stack[stack_top++] = x;     // down
            stack[stack_top++] = y + 1;
        }
        checks++;
    }
}
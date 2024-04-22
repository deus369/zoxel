// based off 1920x1080
const float test_screen_height = 1080;
void fix_for_screen_size(int2 *pixel_size, int2 screen_size) {
    float max_dimension = int2_min(screen_size);
    pixel_size->x = (int) ((pixel_size->x / test_screen_height) * max_dimension);
    pixel_size->y = (int) ((pixel_size->y / test_screen_height) * max_dimension);
}

void fix_text_for_screen_size(int2 *position, int *font_size, int2 screen_size) {
    float max_dimension = int2_min(screen_size);
    *font_size = (int) ((*font_size / test_screen_height) * max_dimension);
    position->x = (int) ((position->x / test_screen_height) * max_dimension);
    position->y = (int) ((position->y / test_screen_height) * max_dimension);
}

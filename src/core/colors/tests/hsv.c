void test_colors_hsv() {
    color test_color = (color) { 130, 148, 191, 255 };
    zox_log(" > color [%ix%ix%i]\n", test_color.r, test_color.g, test_color.b)
    float3 test_hsv = color_to_hsv(test_color);
    zox_log(" > color hsv [%fx%fx%f]\n", test_hsv.x, test_hsv.y, test_hsv.z)
    color test_color2 = hsv_to_color(test_hsv);
    zox_log(" > color converted back [%ix%ix%i]\n", test_color2.r, test_color2.g, test_color2.b)
}

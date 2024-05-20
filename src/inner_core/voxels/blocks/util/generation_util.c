// for now - voxels
int generate_voxel_seed(const unsigned char index) {
    return (rand() % 666666) - 333333 + index;
}

color generate_random_voxel_color() {
    const unsigned char color_margin = 32;
    return (color) { color_margin + rand() % (255 - color_margin * 2), color_margin + rand() % (255 - color_margin * 2), color_margin + rand() % (255 - color_margin * 2), 255 };
}

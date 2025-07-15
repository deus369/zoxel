// for now - voxels
int generate_voxel_seed(const byte index) {
    return (rand() % 666666) - 333333 + index;
}

color generate_random_voxel_color() {
    const byte color_margin = 32;
    return (color) { color_margin + rand() % (255 - color_margin * 2), color_margin + rand() % (255 - color_margin * 2), color_margin + rand() % (255 - color_margin * 2), 255 };
}

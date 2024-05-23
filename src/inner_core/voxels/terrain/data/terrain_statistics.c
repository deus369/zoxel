int zox_statistics_chunks_visible;
int zox_statistics_chunks_total;
int zox_statistics_characters_visible;
int zox_statistics_characters_rendered;
int zox_statistics_characters_total;
int zox_statistics_block_voxes_visible;
int zox_statistics_block_voxes_total;

void update_terrain_statistics() {
    zox_statistics_chunks_visible = 0;
    zox_statistics_chunks_total = 0;
    zox_statistics_characters_visible = 0;
    zox_statistics_characters_rendered = 0;
    zox_statistics_characters_total = 0;
    zox_statistics_block_voxes_visible = 0;
    zox_statistics_block_voxes_total = 0;
}

unsigned char test_read_byte = 255;
unsigned char test_read_byte2 = 255;
extern unsigned char is_steam_running;

void test_steam_cloud() {
#ifdef zox_include_steam
    if (is_steam_running) {
        const char *save_file_name = "zoxel_save";
        const int32_t default_file_length = 2;
        int32_t *file_length = malloc(sizeof(int32_t));
        // zox_log(" > sizeof(int32_t) [%i]\n", sizeof(int32_t))
        *file_length = 0;
        unsigned char* test_bytes_read = steam_remote_read(save_file_name, file_length);
        if (test_bytes_read && file_length && *file_length == default_file_length) {
            test_read_byte = test_bytes_read[0];
            test_read_byte2 = test_bytes_read[1];
            zox_log(" > read bytes [%i:%i] length [%i]\n", test_read_byte, test_read_byte2, *file_length)
        } else {
            test_read_byte = 0;
            test_read_byte2 = 1;
            zox_log(" > creating new data [%i:%i] length [%i]\n", test_read_byte, test_read_byte2, *file_length)
        }
        free(test_bytes_read);
        free(file_length);
        test_read_byte++;
        // write to file
        unsigned char* test_bytes_write = malloc(default_file_length);
        test_bytes_write[0] = test_read_byte;
        test_bytes_write[1] = test_read_byte2;
        if (!steam_remote_save(save_file_name, test_bytes_write, default_file_length)) {
            zox_logg(" > error saving to cloud saves\n")
        } /*else {
            zox_logg(" > success saving to cloud saves\n")
        }*/
        free(test_bytes_write);
    } else {
        // note: sometimes after pushing itll take time before you can activate it
        zox_logg(" > steam is not initialized, cannot test steam cloud\n")
    }
#endif
}

// atm using 127.0.0.1 for same machine testing
// later for secure packets, keep sending with udp every x seconds
#define server_ip (byte4) { 194, 195, 251, 84 }  //  "192.0.2.1"
#define local_server_ip (byte4) { 127, 0, 0, 1 }  //  "192.0.2.1"
#define PORT 12345
#define SERVER_PORT 12346
#define BUFFER_SIZE 128 // 1024 // the size of the buffer to use for receiving and sending data
#define ZOXEL_URL "https://zoxel.duckdns.org"
byte zox_is_networking = 0;
byte server_mode = 0;

void process_arguments_networking(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "-x") == 0 || strcmp(args[i], "--server") == 0) {
            server_mode = 1;
        } else if (strcmp(args[i], "--client") == 0) {
            server_mode = 0;
        } else if (strcmp(args[i], "-x") == 0 || strcmp(args[i], "--server") == 0) {
            server_mode = 1;
        }
    }
}

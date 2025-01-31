// atm using 127.0.0.1 for same machine testing
// later for secure packets, keep sending with udp every x seconds
#define server_ip (byte4) { 194, 195, 251, 84 }  //  "192.0.2.1"
#define local_server_ip (byte4) { 127, 0, 0, 1 }  //  "192.0.2.1"
#define PORT 12345
#define SERVER_PORT 12346
#define BUFFER_SIZE 128 // 1024 // the size of the buffer to use for receiving and sending data
#define ZOXEL_URL "https://zoxel.duckdns.org"
unsigned char server_mode = 0;

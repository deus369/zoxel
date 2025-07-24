#ifdef zoxel_on_windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif
#include <fcntl.h>  // F_SETFL etc
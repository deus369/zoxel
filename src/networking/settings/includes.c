#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif
#include <fcntl.h>  // F_SETFL etc
#include <unistd.h> // close function kept her
// #include <arpa/inet.h>  // sockaddr_in
// SOCK_STREAM = TCP, SOCK_DGRAM = UDP
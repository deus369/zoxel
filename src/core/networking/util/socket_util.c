// #include <arpa/inet.h>  // sockaddr_in
#include <sys/socket.h>
#include <fcntl.h>  // F_SETFL etc
// SOCK_STREAM = TCP, SOCK_DGRAM = UDP

//! Returns socket integer, -1 if failed to bind socket.
int open_socket(int port)
{
    // create the UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("open_socket: socket");
        return -1;
    }
    // set the socket to non-blocking mode
    int flags = fcntl(sock, F_GETFL, 0);
    if (flags < 0)
    {
        perror("open_socket: fcntl");
        return -1;
    }
    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        perror("open_socket: fcntl");
        return -1;
    }
    // set up the address to bind to
    struct sockaddr_in bind_addr;
    memset(&bind_addr, 0, sizeof(bind_addr));
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_addr.s_addr = INADDR_ANY;
    bind_addr.sin_port = htons(port);
    // bind the socket to the address
    if (bind(sock, (struct sockaddr*)&bind_addr, sizeof(bind_addr)) < 0)
    {
        perror("open_socket: bind");
        return -1;
    }
    return sock;
}
byte sockets_enabled = 0;
#ifndef zoxel_on_windows
    #define peek_packet_size 1
    #define socket_error_code -1
    const unsigned long non_blocking = O_NONBLOCK;
    const unsigned long f_getfl = F_GETFL;
    const unsigned long f_setfl = F_SETFL;

    int set_non_blocking(int sock) {
        int flags = fcntl(sock, f_getfl, 0);
        if (flags < 0) {
            perror("    open_socket: fcntl ");
            return 1;
        }
        if (fcntl(sock, f_setfl, flags | non_blocking) < 0) {
            perror("    open_socket: fcntl ");
            return 1;
        }
        return 0;
    }
#else
    #define peek_packet_size 1024
    #define socket_error_code SOCKET_ERROR
    const unsigned long non_blocking = 1; // O_NONBLOCK
    const unsigned long f_getfl = 3; // F_GETFL 
    const unsigned long f_setfl = 4; // F_SETFL

    void initialize_windows_sockets() {
        if (sockets_enabled) return;
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            int error_code = WSAGetLastError();
            zox_log("    open_socket: WSAStartup failed with error code %d\n", error_code)
        } else {
            sockets_enabled = 1;
            zox_log(" + enabled windows sockets\n")
        }
    }

    void dispose_windows_sockets() {
        if (!sockets_enabled) return;
        WSACleanup();
    }

    int set_non_blocking(int sock) {
        // Set the socket to non-blocking mode
        u_long non_blocking = 1;
        if (ioctlsocket(sock, FIONBIO, &non_blocking) != 0) {
            perror(" ! open_socket: ioctlsocket");
            // closesocket(sock);
            return -1;
        }
        return 0;
    }
#endif

    //! Returns socket integer, -1 if failed to bind socket.
    int open_socket(int port) {
        // create the UDP socket
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) {
            perror("    open_socket: socket ");
            return -1;
        }
        if (set_non_blocking(sock)) {
            return -1;
        }
        // set up the address to bind to
        struct sockaddr_in bind_addr;
        memset(&bind_addr, 0, sizeof(bind_addr));
        bind_addr.sin_family = AF_INET;
        bind_addr.sin_addr.s_addr = INADDR_ANY;
        bind_addr.sin_port = htons(port);
        // bind the socket to the address
        if (bind(sock, (struct sockaddr*) &bind_addr, sizeof(bind_addr)) < 0) {
            perror("    open_socket: bind");
            return -1;
        }
        zox_log(" > success opening socket [%i] port [%i]\n", sock, port)
        return sock;
    }


int check_socket_error(char *debug) {
#ifdef zoxel_on_windows
    // Handle errors on Windows
    int error_code = WSAGetLastError();
    if (error_code != WSAEWOULDBLOCK) {
        zox_log(" ! [%s] error_code %d\n", debug, error_code)
    }
    return error_code;
#else
    // Handle errors on Unix-like systems
    if (!(errno == EAGAIN || errno == EWOULDBLOCK)) {
        perror("    check_socket_error: recvfrom");
        zox_log(" ! [%s]\n", debug)
    }
    return errno;
#endif
}

byte peek_at_packet(int socket, struct sockaddr_in *recv_addr) {
    socklen_t recv_addr_len = sizeof(*recv_addr);
    byte recv_buffer[peek_packet_size];
    int recv_size = recvfrom(socket, (char *) recv_buffer, peek_packet_size, MSG_PEEK, (struct sockaddr*) recv_addr, &recv_addr_len);
    if (recv_size < 0) {
        check_socket_error("peek_at_packet");
        return 0;
    } else if (recv_size == 0) {
        return 0;
    } else {
#ifdef zox_testing_networking
        zox_log(" > client packet recieved [%i]\n", recv_buffer[0])
        // zox_log("     - sender ip [%s]\n", ip4_to_string(*recv_addr));
#endif
        return recv_buffer[0];
    }
    return 0;
}

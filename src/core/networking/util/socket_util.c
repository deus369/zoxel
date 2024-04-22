#ifndef zoxel_on_windows
    const unsigned long non_blocking = O_NONBLOCK;
    const unsigned long f_getfl = F_GETFL;
    const unsigned long f_setfl = F_SETFL;

    //! Returns socket integer, -1 if failed to bind socket.
    int open_socket(int port) {
        // create the UDP socket
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) {
            perror("    open_socket: socket ");
            return -1;
        }
        // set the socket to non-blocking mode
        int flags = fcntl(sock, f_getfl, 0);
        if (flags < 0) {
            perror("    open_socket: fcntl ");
            return -1;
        }
        if (fcntl(sock, f_setfl, flags | non_blocking) < 0) {
            perror("    open_socket: fcntl ");
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
        zoxel_log(" > success opening socket [%i] port [%i]\n", sock, port);
        return sock;
    }

#else
    const unsigned long non_blocking = 1; // O_NONBLOCK
    const unsigned long f_getfl = 3; // F_GETFL 
    const unsigned long f_setfl = 4; // F_SETFL
    int open_socket(int port) {
        return 0;
    }
#endif

#include <stdio.h>
#include <stdlib.h> // for malloc, free
#include <string.h> // for strlen
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>     // for write function
#include <fcntl.h>      // for fcntl function
#include <errno.h>

int num_clients = 0;
int web_sock;
int server_port = 80;
// char* html_index = "index.html";
char* html_index = "index_mini.html";
char* response = NULL;
// char *inline_response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Website home was not found.</h1></body></html>\n";

void close_socket() {
    close(web_sock);
}

void make_socket_non_blocking(int web_sock) {
    int flags;
    flags = fcntl(web_sock, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        return;
    }
    flags |= O_NONBLOCK;
    if (fcntl(web_sock, F_SETFL, flags) == -1) {
        perror("fcntl");
        return;
    }
}

int initialize_sockets() {
    struct sockaddr_in server;

    // Create socket
    web_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (web_sock == -1) {
        printf("Could not create socket");
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(server_port);

    // Bind
    if (bind(web_sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        // print the error message
        perror("bind failed. Error");
        return 1;
    }

    // Make the socket non-blocking
    make_socket_non_blocking(web_sock);
    
    if (!is_terminal_ui) {
        puts("bind done");
    }
    return 0;
}

void start_listening() {
    listen(web_sock, 3);
    if (!is_terminal_ui) {
        puts("start_listening");
    }
}

extern int running;
extern int exit_reason;

void accept_incoming_connections(int web_sock, char *response) {
    int client_sock, c, read_size;
    struct sockaddr_in client;
    char client_message[2000];
    c = sizeof(struct sockaddr_in);
    // accept connection from an incoming client
    client_sock = accept(web_sock, (struct sockaddr *) &client, (socklen_t *) &c);
    if (client_sock < 0) {
        if (!(errno == EAGAIN || errno == EWOULDBLOCK)) {
            if (!is_terminal_ui) {
                perror("accept_incoming_connections: accept failed");
            }
        }
        return;
    }
    if (is_terminal_ui == 0) {
        puts("Connection accepted");
    }
    num_clients++;
    is_dirty = 1;
    // Receive a message from client
    if ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
        // Send the response to the client
        if (is_terminal_ui == 0) {
            puts("Sending response to client.");
        }
        write(client_sock, response, strlen(response));
        // printf("%s \n", response);
        // running = 0;
        // exit_reason = 255;
    } else if (read_size == -1) {
        perror("recv failed");
    }
    // Close the client socket
    close(client_sock);
}

char* build_http_response(const char* html_file_buffer) {
    char* response_output = malloc(strlen(html_file_buffer) * sizeof(char) + 256);
    sprintf(response_output, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n%s\n", html_file_buffer);
    return response_output;
}

int load_html() {
    char* html_file = load_file(html_index);
    if (html_file == NULL) {
        return 1;
    }
    if (response != NULL) {
        free(response);
    }
    response = build_http_response(html_file);
    free(html_file);
    return 0;
}

void update_html() {
    if (was_modified(html_index)) {
        if (load_html()) {
            set_mod_time(html_index);   // set file as dirty only when successfully loads
        }
    }
}

void update_web() {
    update_html();
    accept_incoming_connections(web_sock, response);
}

int open_web() {
    if (initialize_sockets()) {
        return 1;
    }
    set_mod_time(html_index);
    load_html();
    return 0;
}

void close_web() {
    close_socket();
    free(response);
}
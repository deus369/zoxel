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
int does_socket_exist = 0;
int server_port = 8080; // 80 - im rerouting this traffic from 80 to 8080 internally
int is_minify = 1;
char* html_index = "index.html";
char* html_index_minify = "index_mini.html";
char* response = NULL;
int has_loaded_html = 0;
// char *inline_response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Website home was not found.</h1></body></html>\n";

void close_socket() {
    if (does_socket_exist) {
        close(web_sock);
        does_socket_exist = 0;
    }
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
    if (does_socket_exist) {
        return 0;
    }
    struct sockaddr_in server;
    web_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (web_sock == -1) {
        printf("Could not create socket");
        return 1;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(server_port);
    if (bind(web_sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind failed. Error");
        return 1;
    }
    does_socket_exist = 1;
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

int accept_incoming_connections(int web_sock, char *response) {
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
        return 1;
    }
    if (is_terminal_ui == 0) {
        puts("Connection accepted");
    }
    num_clients++;
    is_dirty = 1;
    // Receive a message from client
    if ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
        if (is_terminal_ui == 0) {
            puts("Sending response to client.");
        }
        write(client_sock, response, strlen(response));     // Send the response packet to the client
    } else if (read_size == -1) {
        perror("recv failed");
    }
    // Close the client socket
    close(client_sock);
    return 0;   // no error
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
    if (has_loaded_html) {
        free(response);
    } else {
        has_loaded_html = 1;
    }
    response = build_http_response(html_file);
    free(html_file);
    return 0;
}

void update_html(char* html_filepath) {
    if (was_modified(html_filepath)) {
        if (load_html()) {
            set_mod_time(html_filepath);   // set file as dirty only when successfully loads
        }
    }
}

void update_web() {
    if (is_minify)
        update_html(html_index_minify);
    else
        update_html(html_index);
    accept_incoming_connections(web_sock, response);
}

int open_web() {
    if (initialize_sockets()) {
        return 1;
    }
    if (is_minify)
        set_mod_time(html_index_minify);
    else
        set_mod_time(html_index);
    load_html();
    return 0;
}

void close_web() {
    close_socket();
    if (has_loaded_html) {
        free(response);
        has_loaded_html = 0;
    }
}
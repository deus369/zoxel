#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int run_packet_test()
{
    printf("Running test packet_test.\n");
    // set up the address to send to
    struct sockaddr_in send_addr;
    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.s_addr = inet_addr(IP_TO); // replace with the destination IP address
    send_addr.sin_port = htons(PORT_TO);
    // send a message to the destination
    char send_buffer[BUFFER_SIZE];
    strcpy(send_buffer, "Hello, World!");
    ssize_t send_size = sendto(sock, send_buffer, strlen(send_buffer), 0,
        (struct sockaddr*) &send_addr, sizeof(send_addr));
    if (send_size < 0) {
        perror("sendto");
        return 1;
    }
    printf("Sent packet.\n");
    return 0;
}
    
    /*
    // receive a message from the sender
    char recv_buffer[BUFFER_SIZE];
    struct sockaddr_in recv_addr;
    socklen_t recv_addr_len = sizeof(recv_addr);
    ssize_t recv_size = recvfrom(sock, recv_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&recv_addr, &recv_addr_len);
    if (recv_size < 0) {
        perror("recvfrom");
        return 1;
    }

    // print the received message
    recv_buffer[recv_size] = '\0'; // null-terminate the received data
    printf("Received message: %s\n", recv_buffer);
    */

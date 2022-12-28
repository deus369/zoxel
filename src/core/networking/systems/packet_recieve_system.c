//! Called in ecs updates
void PacketRecieveSystem(ecs_iter_t *it)
{
    const NetAddress *netAddresss = ecs_field(it, NetAddress, 2);
    // player positions
    for (int i = 0; i < it->count; i++)
    {
        const NetAddress *netAddress = &netAddresss[i];
        // do the thing
    }
    // just one for now
    // printf("Recieving messages.\n");
    // receive a message from the sender
    char recv_buffer[BUFFER_SIZE];
    struct sockaddr_in recv_addr;
    socklen_t recv_addr_len = sizeof(recv_addr);
    ssize_t recv_size = recvfrom(sock, recv_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&recv_addr, &recv_addr_len);
    if (recv_size < 0) {
        // perror("PacketRecieveSystem - recvfrom");
        return; // 1;
    }

    // print the received message
    recv_buffer[recv_size] = '\0'; // null-terminate the received data
    printf("Received message: %s\n", recv_buffer);
}
ECS_SYSTEM_DECLARE(PacketRecieveSystem);
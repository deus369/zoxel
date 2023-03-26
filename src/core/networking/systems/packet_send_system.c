double last_time_send = 0;
const int test_send_packet_length = 1; // 100;    // 3

//! Atm this is just testing sending to server and getting replies.
void PacketSendSystem(ecs_iter_t *it) {
    // every 3 seconds send one packet!
    last_time_send += it->delta_time;
    if (last_time_send < 3.0) {
        return;
    }
    last_time_send -= 3.0;
    const SocketLink *socketLinks = ecs_field(it, SocketLink, 2);
    const TargetNetAddress *targetNetAddresss = ecs_field(it, TargetNetAddress, 3);
    const TargetNetPort *targetNetPorts = ecs_field(it, TargetNetPort, 4);
    // player positions
    for (int i = 0; i < it->count; i++) {
        const SocketLink *socketLink = &socketLinks[i];
        const TargetNetAddress *targetNetAddress = &targetNetAddresss[i];
        const TargetNetPort *targetNetPort = &targetNetPorts[i];
        struct sockaddr_in send_addr = byte4_to_ip(targetNetAddress->value, targetNetPort->value);
        unsigned char packet_size = 1;
        unsigned char send_buffer[] = { zoxel_packet_type_connect };
        const char *send_text = "Hello World.";
        unsigned char *send_buffer_2 = convert_from_ascii_text_at(send_text, 2);
        send_buffer_2[0] = zoxel_packet_type_msg;
        send_buffer_2[1] = strlen(send_text);
        unsigned char packet_size_2 = 2 + send_buffer_2[1];
        unsigned char packets_send_count = 1 + rand() % test_send_packet_length;
        zoxel_log("Sending [%i] packets\n", packets_send_count);
        // test sending multiple times
        for (int j = 0; j < packets_send_count; j++) {
            if (rand() % 100 >= 70) {
                // send text instead
                ssize_t send_size = sendto(socketLink->value, (const char *) send_buffer_2, packet_size_2, 0,
                    (struct sockaddr*) &send_addr, sizeof(send_addr));
                if (send_size < 0) {
                    perror("sendto");
                } else {
                   // zoxel_log("Sent packet type [%i] - [%s].\n", send_buffer_2[0], send_text);
                }
            } else {
                ssize_t send_size = sendto(socketLink->value, (const char *) send_buffer, packet_size, 0, (struct sockaddr*) &send_addr, sizeof(send_addr));
                if (send_size < 0) {
                    perror("sendto");
                } else {
                    // zoxel_log("Sent packet type [%i].\n", send_buffer[0]);
                }
            }
        }
        free(send_buffer_2);
    }
}
zoxel_declare_system(PacketSendSystem)
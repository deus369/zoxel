double last_time_send = 0;
const int test_send_packet_length = 1; // 100;    // 3

//! Atm this is just testing sending to server and getting replies
void PacketSendSystem(ecs_iter_t *it) {
    // every 3 seconds send one packet!
    init_delta_time()
    last_time_send += delta_time;
    if (last_time_send < 3.0) return;
    last_time_send -= 3.0;
    zox_field_in(SocketLink, socketLinks, 2)
    zox_field_in(TargetNetAddress, targetNetAddresss, 3)
    zox_field_in(TargetNetPort, targetNetPorts, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(SocketLink, socketLinks, socketLink)
        zox_field_i(TargetNetAddress, targetNetAddresss, targetNetAddress)
        zox_field_i(TargetNetPort, targetNetPorts, targetNetPort)
        struct sockaddr_in send_addr = byte4_to_ip(targetNetAddress->value, targetNetPort->value);
        byte packet_size = 1;
        byte send_buffer[] = { zoxel_packet_type_connect };
        const char *send_text = "Hello World.";
        byte *send_buffer_2 = convert_from_ascii_text_at(send_text, 2);
        send_buffer_2[0] = zoxel_packet_type_msg;
        send_buffer_2[1] = strlen(send_text);
        byte packet_size_2 = 2 + send_buffer_2[1];
        byte packets_send_count = 1 + rand() % test_send_packet_length;
#ifdef zox_testing_networking
        zox_log(" > sending [%i] packets to [%i.%i.%i.%i:%i]\n", packets_send_count, targetNetAddress->value.x, targetNetAddress->value.y, targetNetAddress->value.z, targetNetAddress->value.w, targetNetPort->value)
#endif
        // test sending multiple times
        for (int j = 0; j < packets_send_count; j++) {
            if (rand() % 100 >= 70) {
                // send text instead
                int send_size = sendto(socketLink->value, (const char *) send_buffer_2, packet_size_2, 0, (struct sockaddr*) &send_addr, sizeof(send_addr));
                if (send_size == socket_error_code) {
                    check_socket_error("send_system");
                } else {
                   // zox_log("Sent packet type [%i] - [%s].\n", send_buffer_2[0], send_text);
                }
            } else {
                int send_size = sendto(socketLink->value, (const char *) send_buffer, packet_size, 0, (struct sockaddr*) &send_addr, sizeof(send_addr));
                if (send_size == socket_error_code) {
                    check_socket_error("send_system2");
                } else {
                    // zox_log("Sent packet type [%i].\n", send_buffer[0]);
                }
            }
        }
        free(send_buffer_2);
    }
} zox_declare_system(PacketSendSystem)

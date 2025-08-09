void PacketRecieveSystem(ecs_iter_t *it) {
    byte recv_buffer[1];
    zox_sys_begin()
    zox_sys_in(SocketLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(SocketLink, socketLink)
        if (!socketLink->value) {
            continue;
        }
        int recv_size;
        struct sockaddr_in recv_addr;
        socklen_t recv_addr_len = sizeof(recv_addr);
        while (1) {
            byte is_consume_packet = 1;
            byte packet_size = 1;
            const byte packet_type = peek_at_packet(socketLink->value, &recv_addr);
            if (packet_type == 0) break;  // No more packets to process
            // zox_log(" > received packet [%i] from [%s]\n", packet_type, ip4_to_string(recv_addr)) // , recv_size);
            if (packet_type == zoxel_packet_type_connect) {
                // reply to client to confirm message was sent
                byte return_packet_size = 1;
                byte send_buffer[1] = { zoxel_packet_type_connect_confirm };   // return packet
                int send_size = sendto(socketLink->value, (const char *) send_buffer, return_packet_size, 0, (struct sockaddr*) &recv_addr, sizeof(recv_addr));
                if (send_size == socket_error_code) {
                    check_socket_error("recieve_system");
                } else {
                    zox_log("    - sent return packet type [%i].\n", send_buffer[0]);
                }
            } else if (packet_type == zoxel_packet_type_connect_confirm) {
                zox_log("    - client is confirmed to join server.\n");
            } else if (packet_type == zoxel_packet_type_msg_confirm) {
                zox_log("    - message has reached the server.\n");
            } else if (packet_type == zoxel_packet_type_msg) {
                byte recv_buffer_2[1 + peek_packet_size];
                int text_size2 = recvfrom(socketLink->value, (char *) recv_buffer_2, 1 + peek_packet_size, MSG_PEEK, (struct sockaddr*) &recv_addr, &recv_addr_len);
                if (text_size2 == socket_error_code) {
                    check_socket_error("recieve_system2");
                } else {
                    byte text_length = recv_buffer_2[1];
                    zox_log("    - server recieved message of size [%i]\n", text_length);
                    packet_size = 2 + text_length;
                    byte recv_buffer_3[packet_size];
                    is_consume_packet = 0;
                    recv_size = recvfrom(socketLink->value, (char *) recv_buffer_3, packet_size, 0, (struct sockaddr*) &recv_addr, &recv_addr_len);
                    if (recv_size == socket_error_code) {
                        check_socket_error("recieve_system3");
                        // perror("    PacketRecieveSystem : zoxel_packet_type_msg 2 : recvfrom");
                    } else {
                        char* text = convert_to_ascii_text_at(recv_buffer_3, text_length, 2);
                        zox_log("        - message [%s]\n", text);
                        free(text);
                    }
                }
            }
            if (is_consume_packet) {
                recv_size = recvfrom(socketLink->value, (char *) recv_buffer, 1, 0, (struct sockaddr*) &recv_addr, &recv_addr_len);
            }
            if (recv_size > packet_size) {
                zox_log("    - multiple packets to read detected.\n");
                continue;   // more packets to read
            } /*else {
                // break;  // no more packets to read
                // zox_log(" > no packet recieved\n");
            }*/
            break;
        }
    }
    // zox_log(" === finished attempting to get packets ===\n");
} zoxd_system(PacketRecieveSystem)

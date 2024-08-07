unsigned char peek_at_packet(int socket, struct sockaddr_in *recv_addr) {
    socklen_t recv_addr_len = sizeof(recv_addr);
    unsigned char recv_buffer[1];
    ssize_t recv_size = recvfrom(socket, (char *) recv_buffer, 1, MSG_PEEK, (struct sockaddr*) recv_addr, &recv_addr_len);
    if (recv_size < 0) {
        // these errors handle no data recieved
        if (!(errno == EAGAIN || errno == EWOULDBLOCK)) perror("    PacketRecieveSystem: recvfrom ");    // an error occurred, print the error and exit
        return 0;
    } else if (recv_size == 0) {
        return 0;
    } else {
        // zoxel_log(" > client packet recieved [%i]\n", recv_buffer[0]);
        // zoxel_log("     - sender ip [%s]\n", ip4_to_string(*recv_addr));
        return recv_buffer[0];
    }
    return 0;
}

void PacketRecieveSystem(ecs_iter_t *it) {
    // zoxel_log(" === attempting to get packets ===\n");
    // only for PacketListener tagged entities
    // zox_iter_world()
    zox_field_in(SocketLink, socketLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(SocketLink, socketLinks, socketLink)
        if (socketLink->value == 0) continue;
        ssize_t recv_size;
        struct sockaddr_in recv_addr;
        socklen_t recv_addr_len = sizeof(recv_addr);
        unsigned char recv_buffer[1];
        while (1) {
            unsigned char is_consume_packet = 1;
            unsigned char packet_size = 1;
            unsigned char packet_type = peek_at_packet(socketLink->value, &recv_addr);
            if (packet_type != 0) {
                zoxel_log(" > received packet [%i] from [%s]\n", packet_type, ip4_to_string(recv_addr)); // , recv_size);
                if (packet_type == zoxel_packet_type_connect) {
                    // reply to client to confirm message was sent
                    // if (zox_has(it->entities[i], NetRoom))
                    {
                        unsigned char return_packet_size = 1;
                        unsigned char send_buffer[1] = { zoxel_packet_type_connect_confirm };   // return packet
                        ssize_t send_size = sendto(socketLink->value, (const char *) send_buffer, return_packet_size, 0,
                             (struct sockaddr*) &recv_addr, sizeof(recv_addr));
                        if (send_size < 0) {
                            perror("    PacketRecieveSystem : zoxel_packet_type_connect : sendto ");
                        } else {
                            zoxel_log("    - sent return packet type [%i].\n", send_buffer[0]);
                        }
                    }
                } else if (packet_type == zoxel_packet_type_connect_confirm) {
                    zoxel_log("    - client is confirmed to join server.\n");
                } else if (packet_type == zoxel_packet_type_msg_confirm) {
                    zoxel_log("    - message has reached the server.\n");
                } else if (packet_type == zoxel_packet_type_msg) {
                    unsigned char recv_buffer_2[2];
                    ssize_t text_size2 = recvfrom(socketLink->value, (char *) recv_buffer_2, 2, MSG_PEEK, (struct sockaddr*) &recv_addr, &recv_addr_len);
                    if (text_size2 < 0) {
                        perror("    PacketRecieveSystem : zoxel_packet_type_msg : recvfrom ");
                    } else {
                        unsigned char text_length = recv_buffer_2[1];
                        zoxel_log("    - server recieved message of size [%i]\n", text_length);
                        packet_size = 2 + text_length;
                        unsigned char recv_buffer_3[packet_size];
                        is_consume_packet = 0;
                        recv_size = recvfrom(socketLink->value, (char *) recv_buffer_3, packet_size, 0, (struct sockaddr*) &recv_addr, &recv_addr_len);
                        if (recv_size < 0) {
                            perror("    PacketRecieveSystem : zoxel_packet_type_msg 2 : recvfrom");
                        } else {
                            char* text = convert_to_ascii_text_at(recv_buffer_3, text_length, 2);
                            zoxel_log("        - message [%s]\n", text);
                            free(text);
                        }
                    }
                }
                if (is_consume_packet) {
                    recv_size = recvfrom(socketLink->value, (char *) recv_buffer, 1, 0, (struct sockaddr*) &recv_addr, &recv_addr_len);
                }
                if (recv_size > packet_size) {
                    zoxel_log("    - multiple packets to read detected.\n");
                    continue;   // more packets to read
                }
            } /*else {
                // break;  // no more packets to read
                // zoxel_log(" > no packet recieved\n");
            }*/
            break;
        }
    }
    // zoxel_log(" === finished attempting to get packets ===\n");
} zox_declare_system(PacketRecieveSystem)

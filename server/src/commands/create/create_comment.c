/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

void send_comment_packet(struct client_s *cli, struct comment_s *new)
{
    struct packet_server_s packet = {0};

    packet.command = 27;
    memcpy(packet.thread_id, cli->thread->uuid, sizeof(packet.thread_id));
    memcpy(packet.user_id, cli->user->uuid, sizeof(packet.user_id));
    memcpy(&packet.time_stamp, &new->timestamp, sizeof(packet.time_stamp));
    memcpy(packet.body, new->body, sizeof(new->body));
    add_to_buffer_list(cli, packet);
}

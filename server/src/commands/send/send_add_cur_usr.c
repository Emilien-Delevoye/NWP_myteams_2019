/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>

void add_to_current_usr(struct packet_server_s packet, struct client_s *cli)
{
    struct list_msg_cli_s *act = cli->user->msg;
    struct list_msg_cli_s *new = malloc(sizeof(struct list_msg_cli_s));

    if (!new)
        return;
    memset(new, 0, sizeof(struct list_msg_cli_s));
    strcpy(new->uuid_tx, packet.team_id);
    strcpy(new->uuid_rx, packet.user_id);
    strcpy(new->msg, packet.body);
    new->next = NULL;
    new->timestamp = packet.time_stamp;
    if (!act) {
        cli->user->msg = new;
    } else {
        while (act->next)
            act = act->next;
        act->next = new;
    }
}

/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>

void logout_server(char read_buf[BF_S], struct client_s *cli)
{
    char uuid[LUID] = {0};
    char username[33] = {0};

    if (strncmp("logout", read_buf, 6) == 0) {
        client_event_loggedout(cli->user.uuid, cli->user.username);
        cli->server_running = false;
    } else if (strncmp("bogout", read_buf, 6) == 0) {
        memcpy(uuid, read_buf + 6, sizeof(uuid) - 1);
        memcpy(username, read_buf + 6 + sizeof(uuid), sizeof(username) - 1);
        client_event_loggedout(uuid, username);
    }
}
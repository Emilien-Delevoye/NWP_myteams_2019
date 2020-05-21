/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>

void login_server_cli(char read_buf[BF_S], struct client_s *cli)
{
    char uuid[LUID] = {0};
    char username[33] = {0};

    if (strncmp("login", read_buf, 5) == 0) {
        memcpy(cli->user.uuid, read_buf + 6, sizeof(cli->user.uuid) - 1);
        memcpy(cli->user.username, read_buf + 6 + sizeof(cli->user.uuid),
            sizeof(cli->user.username));
        client_event_loggedin(cli->user.uuid, cli->user.username);
    } else if (strncmp("bogin", read_buf, 5) == 0) {
        memcpy(uuid, read_buf + 6, sizeof(uuid) - 1);
        memcpy(username, read_buf + 6 + sizeof(uuid), sizeof(username) - 1);
        client_event_loggedin(uuid, username);
    }
}
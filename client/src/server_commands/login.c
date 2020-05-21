/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>

void login_server(char read_buf[BF_S], struct client_s *cli)
{
    if (strncmp("login", read_buf, 5) == 0) {
        memcpy(cli->user.uuid, read_buf + 6, sizeof(cli->user.uuid));
        memcpy(cli->user.username, read_buf + 7 + sizeof(cli->user.uuid),
            sizeof(cli->user.username));
        client_event_loggedin(cli->user.uuid, cli->user.username);
    } else if (strncmp("bogin", read_buf, 5) == 0) {
        client_event_loggedin(cli->user.uuid, cli->user.username);
    }
}
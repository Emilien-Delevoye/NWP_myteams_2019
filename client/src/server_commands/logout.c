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
    if (strncmp("logout", read_buf, 6) != 0)
        return;
    memcpy(cli->user.uuid, read_buf + 7, sizeof(cli->user.uuid) - 1);
    memcpy(cli->user.username, read_buf + 7 + sizeof(cli->user.uuid),
        sizeof(cli->user.username));
    client_event_loggedout((const char *)cli->user.uuid, cli->user.username);
    cli->server_running = false;
}
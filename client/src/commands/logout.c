/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>

void logout(struct client_s *client, char **command)
{
    char buffer[BF_S] = {0};

    if (strcmp(command[0], "/logout") != 0 || command[1] != NULL)
        return;
    if (*client->user.username == 0 && *client->user.uuid == 0) {
        client->server_running = false;
    } else {
        strcpy(buffer, command[0]);
        add_to_buffer_list(client, command[0]);
    }
}
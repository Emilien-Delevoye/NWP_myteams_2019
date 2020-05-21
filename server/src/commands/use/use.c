/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

void use(char buffer[BF_S], data_server_t *data, struct client_s *client)
{
    char *sep = "|";
    char *create[4] = {NULL, NULL, NULL, NULL};

    create[0] = strtok(buffer, sep);
    create[1] = strtok(NULL, sep);
    create[2] = strtok(NULL, sep);
    create[3] = strtok(NULL, sep);
    if (create[1])
        use_team(create, data, client);
}
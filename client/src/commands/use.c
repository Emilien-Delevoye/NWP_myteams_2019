/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>
#include <stdio.h>

void use(struct client_s *client, char **command)
{
    char buffer[BF_S] = {0};
    int position = -1;

    if (strcmp(command[0], "/use") != 0)
        return;
    if ((command[1] && command[2] != NULL && command[3] != NULL &&
        command[4] != NULL))
        return;
    while (command[0][++position])
        buffer[position] = command[0][position];
    buffer[position] = '|';
    for (int b = 1; command[b]; ++b) {
        for (int a = 0; command[b][a]; ++a)
            buffer[++position] = command[b][a];
        buffer[++position] = '|';
    }
    add_to_buffer_list(client, buffer);
}
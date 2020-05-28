/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

#include <string.h>
#include <stdio.h>

void subscribed(struct client_s *client, char **command)
{
    char buffer[BF_S] = {0};
    int position = -1;

    if (strcmp(command[0], "/subscribed") != 0)
        return;
    if (command[1] != NULL && command[2] != NULL)
        return;
    while (command[0][++position])
        buffer[position] = command[0][position];
    buffer[position] = '|';
    if (command[1])
        for (int a = 0; command[1][a]; ++a)
            buffer[++position] = command[1][a];
    add_to_buffer_list(client, buffer);
}
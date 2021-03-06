/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>
#include <stdio.h>

static void extract_command_create(char **command, char buffer[BF_S])
{
    int position = - 1;

    while (command[0][++position])
        buffer[position] = command[0][position];
    buffer[position] = '|';
    for (int b = 1; command[b]; ++b) {
        for (int a = 0; command[b][a]; ++a)
            buffer[++position] = command[b][a];
        buffer[++position] = '|';
    }
}

void create(struct client_s *client, char **command)
{
    char buffer[BF_S] = {0};

    if (strcmp(command[0], "/create") != 0)
        return;
    if (command[1] == NULL || (command[2] != NULL && command[3] != NULL))
        return;
    extract_command_create(command, buffer);
    add_to_buffer_list(client, buffer);
}
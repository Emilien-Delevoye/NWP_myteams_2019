/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>

void list(struct client_s *client, char **command)
{
    char buffer[BF_S] = {0};
    int position = -1;

    if (strcmp(command[0], "/list") != 0)
        return;
    if (command[1] != NULL) {
        puts(RED"Wrong parameters"DEFAULT);
        return;
    }
    while (command[0][++position])
        buffer[position] = command[0][position];
    buffer[position] = '|';
    fputs("pouet pouet\n", stderr);
    add_to_buffer_list(client, buffer);
}
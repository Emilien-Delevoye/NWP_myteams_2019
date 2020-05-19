/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *command[10] = {"/login", NULL};
void (*fct[10])(char [BF_S], data_server_t *, struct client_s *) =
    {login, NULL};

void interpret_cmd(char buf[BF_S], data_server_t *data, struct client_s *cur)
{
    for (int a = 0; command[a]; ++a)
        if (strncmp(command[a], buf, strlen(command[a])) == 0)
            fct[a](buf, data, cur);
}

void read_buffer(char buffer[BF_S], data_server_t *data, struct client_s *cur)
{
    char to_write[BF_S] = {0};

    printf(YELLOW"[INFO] New packet : %s\n"DEFAULT, buffer);
    strcpy(to_write, "Message receive");
    interpret_cmd(buffer, data, cur);
    add_to_buffer_list(cur, to_write);
}
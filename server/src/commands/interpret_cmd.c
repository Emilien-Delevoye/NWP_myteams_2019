/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

const char *command[10] = {"/login", "/logout", "/create", "/use",
    "/subscribe", "/unsubscribe", "/users", NULL};

void (*fct[])(char [BF_S], data_server_t *, struct client_s *) =
    {login, logout, create, use, subscribe, unsubscribe, users, NULL};

void interpret_cmd(char buf[BF_S], data_server_t *data, struct client_s *cur)
{
    for (int a = 0; command[a]; ++a)
        if (strncmp(command[a], buf, strlen(command[a])) == 0)
            fct[a](buf, data, cur);
}
/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>

void (*tab_fct_commands[14])(struct client_s *client, char **command) =
{
    create, login, logout, messages, send, subscribe, subscribed, unsubscribe,
    use, user, users, list, info, NULL
};

void call_function(struct client_s *client, char **command)
{
    if (!command || !command[0])
        return;
    if (strcmp(command[0], "/login") != 0 && !client->user.username[0] &&
        strcmp(command[0], "/logout") != 0) {
        client_error_unauthorized();
        return;
    }
    for (int a = 0; tab_fct_commands[a]; ++a)
        tab_fct_commands[a](client, command);
}
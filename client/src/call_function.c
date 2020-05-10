/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <stdlib.h>

void (*tab_fct_commands[12])(struct client_s *client, char **command) =
{
    create, login, logout, messages, send, subscribe, subscribed, unsubscribe,
    use, user, users, NULL
};

void call_function(struct client_s *client, char **command)
{
    for (int a = 0; tab_fct_commands[a]; ++a)
        tab_fct_commands[a](client, command);
}
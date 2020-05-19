/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *extract_name(char buffer[BF_S])
{
    char *output = malloc(33);

    if (!output)
        return (NULL);
    for (int a = 7; a < 39; ++a) {
        output[a - 7] = buffer[a];
        output[a - 6] = 0;
    }
    return (output);
}

static struct user_s *get_existing_user(data_server_t *data,
    const char *username)
{
    for (struct user_s *cur = data->l_users; cur; cur = cur->next)
        if (cur->username && strcmp(cur->username, username) == 0)
            return (cur);
    return (NULL);
}

void login(char buffer[BF_S], data_server_t *data, struct client_s *client)
{
    char *name = extract_name(buffer);
    struct user_s *user = NULL;

    if (!name) {
        puts(RED"[ERROR] Malloc error: extract_name()"DEFAULT);
        return;
    }
    user = get_existing_user(data, name);
    printf("Existing user : %s\n", (user != NULL ? user->username : "null"));
    printf(GREEN"[INFO] Connexion utilisateur : %s\n"DEFAULT, name);
}
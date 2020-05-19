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
#include <uuid/uuid.h>

static char *extract_name(const char buffer[BF_S])
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
    for (struct user_s *cur = data->l_users; cur; cur = cur->next) {
        if (cur->username && strcmp(cur->username, username) == 0) {
            server_event_user_loaded((const char *)cur->uuid, cur->username);
            return (cur);
        }
    }
    return (NULL);
}

static void add_to_user_list(data_server_t *data, struct user_s *new)
{
    struct user_s *cur = data->l_users;

    if (!data->l_users) {
        data->l_users = new;
        return;
    }
    while (cur->next)
        cur = cur->next;
    cur->next = new;
}

static struct user_s *add_user(data_server_t *data, char *username)
{
    struct user_s *new;

    if (!username)
        return (NULL);
    new = malloc(sizeof(struct user_s));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->username = username;
    uuid_generate_random(new->uuid);
    printf(GREEN"[INFO] New user \"%s\" created\n"DEFAULT, username);
    add_to_user_list(data, new);
    server_event_user_created((const char *)new->uuid, new->username);
    return (new);
}

void login(char buffer[BF_S], data_server_t *data, struct client_s *client)
{
    char *name = extract_name(buffer);
    struct user_s *user = NULL;

    if (client->user) {
        puts(YELLOW"[INFO] User already logged in"DEFAULT);
        return;
    } else if (!name) {
        puts(RED"[ERROR] Malloc error: extract_name()"DEFAULT);
        return;
    }
    user = get_existing_user(data, name);
    if (!user)
        user = add_user(data, name);
    if (!user)
        return;
    client->user = user;
    printf(GREEN"[INFO] Connexion utilisateur : %s\n"DEFAULT, name);
}
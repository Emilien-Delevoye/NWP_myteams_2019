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
            server_event_user_logged_in((const char *)cur->uuid);
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
    uuid_t uuid;

    if (!username)
        return (NULL);
    new = malloc(sizeof(struct user_s));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->username = username;
    uuid_generate_random(uuid);
    uuid_unparse(uuid, new->uuid);
    printf(GREEN"[INFO] New user \"%s\" created\n"DEFAULT, username);
    add_to_user_list(data, new);
    server_event_user_created(new->uuid, new->username);
    server_event_user_logged_in(new->uuid);
    return (new);
}

void login(char buffer[BF_S], data_server_t *data, struct client_s *client)
{
    char *name = extract_name(buffer);
    char out_buf[BF_S] = {0};

    if (client->user) {
        puts(YELLOW"[INFO] User already logged in"DEFAULT);
        return;
    } else if (!name) {
        puts(RED"[ERROR] Malloc error: extract_name()"DEFAULT);
        return;
    }
    client->user = get_existing_user(data, name);
    if (!client->user)
        client->user = add_user(data, name);
    if (!client->user)
        return;
    create_log_buffer(out_buf, client->user, "login");
    add_to_buffer_list(client, out_buf);
    out_buf[0] = 'b';
    add_to_broadcast_list(data, out_buf, client);
}
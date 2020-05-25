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

static void extract_name(const char buffer[BF_S], char output[33])
{
    for (int a = 7; a < 39; ++a) {
        output[a - 7] = buffer[a];
        output[a - 6] = 0;
    }
}

static struct user_s *get_existing_user(data_server_t *data,
    const char *username)
{
    for (struct user_s *cur = data->l_users; cur; cur = cur->next) {
        if (cur->username[0] && strcmp(cur->username, username) == 0) {
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

static struct user_s *add_user(data_server_t *data, char username[33])
{
    struct user_s *new;
    uuid_t uuid;

    if (!username)
        return (NULL);
    new = malloc(sizeof(struct user_s));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->joined_teams = NULL;
    memcpy(new->username, username, sizeof(new->username));
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
    char name[33] = {0};
    struct packet_server_s packet = {0};

    extract_name(buffer, name);
    if (client->user || !name[0])
        return;
    client->user = get_existing_user(data, name);
    if (!client->user)
        client->user = add_user(data, name);
    if (!client->user)
        return;
    packet.command = 1;
    memcpy(packet.user_id, client->user->uuid, sizeof(packet.user_id));
    memcpy(packet.name, client->user->username, sizeof(packet.name));
    add_to_buffer_list(client, packet);
    packet.broadcast = 1;
    add_to_broadcast_list(data, packet, client);
}
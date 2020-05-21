/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>

static void create_team(char *n[3], data_server_t *data,
    struct client_s *cli)
{
    struct team_s *cur = data->l_teams;
    struct team_s *new;

    if (existing_team(n[1], cur, cli))
        return;
    new = malloc(sizeof(struct team_s));
    if (!new)
        return;
    init_team(n, new, cli, data);
    if (!cur) {
        data->l_teams = new;
    } else {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    }
}

static void create_channel(char *n[3], struct client_s *cli)
{
    struct channel_s *cur = cli->team->channels;
    struct channel_s *new = malloc(sizeof(struct channel_s));

    if (!new)
        return;
    init_channel(n, new, cli);
    if (cli->team->channels) {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    } else {
        cli->team->channels = new;
    }
}

static void create_thread(char *n[3], struct client_s *cli)
{
    struct channel_s *cur = cli->team->channels;
    struct channel_s *new = malloc(sizeof(struct channel_s));

    if (!new)
        return;
    init_channel(n, new, cli);
    if (cli->team->channels) {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    } else {
        cli->team->channels = new;
    }
}

void create(char buffer[BF_S], data_server_t *data, struct client_s *client)
{
    char *sep = "|";
    char *create[3] = {NULL, NULL, NULL};

    create[0] = strtok(buffer, sep);
    create[1] = strtok(NULL, sep);
    create[2] = strtok(NULL, sep);
    if (!client->team && create[1] && create[2])
        create_team(create, data, client);
    if (client->team && !client->thread && create[1] && create[2])
        create_channel(create, client);
    if (client->team && client->thread && create[1] && create[2])
        create_thread(create, client);
}
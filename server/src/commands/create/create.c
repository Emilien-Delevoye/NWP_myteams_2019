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

static void create_channel(char *n[3], struct client_s *cli,
    data_server_t *data)
{
    struct channel_s *cur = cli->team->channels;
    struct channel_s *new;

    if (existing_channel(n[1], cur, cli))
        return;
    new = malloc(sizeof(struct channel_s));
    if (!new)
        return;
    init_channel(n, new, cli, data);
    if (!cur) {
        cli->team->channels = new;
    } else {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    }
}

static void create_thread(char *n[3], struct client_s *cli,
    data_server_t *data)
{
    struct thread_s *cur = cli->channel->threads;
    struct thread_s *new;

    if (existing_thread(n[1], cur, cli))
        return;
    new = malloc(sizeof(struct thread_s));
    if (!new)
        return;
    init_thread(n, new, cli, data);
    if (!cur) {
        cli->channel->threads = new;
    } else {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    }
}

static void create_comment(char *n[3], struct client_s *cli,
    data_server_t *data)
{
    struct comment_s *cur = cli->thread->comments;
    struct comment_s *new = malloc(sizeof(struct comment_s));
    size_t size = strlen(n[1]);

    if (!new)
        return;
    memset(new, 0, sizeof(struct comment_s));
    strncpy(new->body, n[1], (size > 512 ? 512 : size));
    new->timestamp = time(NULL);
    if (!cur) {
        cli->channel->threads->comments = new;
    } else {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    }
    send_comment_packet(cli, new, data);
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
    if (client->team && !client->channel && create[1] && create[2])
        create_channel(create, client, data);
    if (client->team && client->channel && !client->thread && create[1]
        && create[2])
        create_thread(create, client, data);
    if (client->team && client->channel && client->thread && create[1] &&
        !create[2])
        create_comment(create, client, data);
}
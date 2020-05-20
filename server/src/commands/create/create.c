/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static void ping_client_n_team(struct team_s *new, struct client_s *cli)
{
    char buffer[BF_S] = {0};

    strncpy(buffer, "n_team|", 7);
    strncpy(buffer + 7, (const char *)new->uuid, sizeof(new->uuid));
    strncpy(buffer + 7 + sizeof(new->uuid), "|", 1);
    strncpy(buffer + 8 + sizeof(new->uuid), new->name, sizeof(new->name));
    strncpy(buffer + 8 + sizeof(new->uuid) + sizeof(new->name), "|", 1);
    strncpy(buffer + 9 + sizeof(new->uuid) + sizeof(new->name), new->desc,
        sizeof(new->desc));
    write(1, buffer, BF_S);
    add_to_buffer_list(cli, buffer);
}

static void init_team(char *n[3], struct team_s *new, struct client_s *cli)
{
    size_t len_1 = strlen(n[1]);
    size_t len_2 = strlen(n[2]);

    memset(new, 0, sizeof(struct team_s));
    strncpy(new->name, n[1], (len_1 > 32 ? 32 : len_1));
    strncpy(new->desc, n[2], (len_2 > 255 ? 255 : len_2));
    uuid_generate_random(new->uuid);
    remove_pipe_uuid(new->uuid);
    server_event_team_created(U_TC new->uuid, new->name, U_TC cli->user->uuid);
    ping_client_n_team(new, cli);
    new->next = NULL;
}

static void create_team(char *n[3], data_server_t *data,
    struct client_s *cli)
{
    struct team_s *cur = data->l_teams;
    struct team_s *new = malloc(sizeof(struct team_s));

    if (!new)
        return;
    init_team(n, new, cli);
    if (data->l_teams) {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    } else {
        data->l_teams = new;
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
}
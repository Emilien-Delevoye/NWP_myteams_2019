/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>

struct team_s *get_team_by_uuid(char uuid[LUID], data_server_t *data,
    struct client_s *client)
{
    struct packet_server_s packet = {0};

    for (struct team_s *cur = data->l_teams; cur; cur = cur->next)
        if (strcmp(cur->uuid, uuid) == 0)
            return (cur);
    packet.command = 14;
    memcpy(packet.team_id, uuid, sizeof(packet.team_id));
    add_to_buffer_list(client, packet);
    return (NULL);
}

void save_subscribe(struct client_s *cli, struct list_team_cli_s *cur[2],
    struct team_s *team)
{
    struct packet_server_s packet = {0};

    cur[1]->team = team;
    cur[1]->next = NULL;
    if (!cli->user->joined_teams) {
        cli->user->joined_teams = cur[1];
    } else {
        while (cur[0]->next)
            cur[0] = cur[0]->next;
        cur[0]->next = cur[1];
    }
    packet.command = 28;
    memcpy(packet.user_id, cli->user->uuid, sizeof(packet.user_id));
    memcpy(packet.team_id, team->uuid, sizeof(packet.team_id));
    add_to_buffer_list(cli, packet);
    server_event_user_join_a_team(packet.team_id, packet.user_id);
}

static void already_exist(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    packet.command = 19;
    add_to_buffer_list(cli, packet);
}

void subscribe(char buffer[BF_S], data_server_t *data, struct client_s *client)
{
    struct list_team_cli_s *cur[2] = {client->user->joined_teams, NULL};
    char uuid[LUID] = {0};
    struct team_s *team;

    memcpy(uuid, buffer + 11, sizeof(uuid) - 1);
    team = get_team_by_uuid(uuid, data, client);
    if (!team)
        return;
    for (list_team_cli_t *c = client->user->joined_teams; c; c = c->next) {
        if (c->team == team) {
            already_exist(client);
            return;
        }
    }
    cur[1] = malloc(sizeof(struct list_team_cli_s));
    if (!cur[1])
        return;
    save_subscribe(client, cur, team);
}
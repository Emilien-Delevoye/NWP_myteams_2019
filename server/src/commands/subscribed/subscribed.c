/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

static void list_sub_by_user(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    if (!cli->user)
        return;
    for (struct list_team_cli_s *cur = cli->user->joined_teams; cur;
        cur = cur->next) {
        packet.command = 9;
        memcpy(packet.team_id, cur->team->uuid, sizeof(packet.team_id));
        memcpy(packet.name, cur->team->name, sizeof(cur->team->name));
        memcpy(packet.description, cur->team->desc, sizeof(cur->team->desc));
        add_to_buffer_list(cli, packet);
    }
}

static void send_user(struct user_s *usr, struct client_s *cli,
    data_server_t *data)
{
    struct packet_server_s packet = {0};

    packet.command = 8;
    memcpy(packet.user_id, usr->uuid, sizeof(packet.user_id));
    memcpy(packet.name, usr->username, sizeof(packet.name));
    packet.user_status = get_status_user(data, usr);
    add_to_buffer_list(cli, packet);
}

void find_team(data_server_t *data, const struct team_s *team,
    struct client_s *cli)
{
    for (struct user_s *cur = data->l_users; cur; cur = cur->next) {
        for (struct list_team_cli_s *joi = cur->joined_teams; joi;
            joi = joi->next) {
            if (strcmp(team->uuid, joi->team->uuid) == 0)
                send_user(cur, cli, data);
        }
    }
}

void list_sub_by_team(data_server_t *data, struct client_s *cl, char id[LUID])
{
    for (struct team_s *team = data->l_teams; team; team = team->next) {
        if (strcmp(team->uuid, id) == 0) {
            find_team(data, team, cl);
            return;
        }
    }
    send_unk_team(cl, id);
}

void subscribed(char buffer[BF_S], data_server_t *data, struct client_s *cli)
{
    char uuid[LUID];

    memcpy(uuid, buffer + 12, sizeof(uuid));
    if (strlen(uuid) == 0)
        list_sub_by_user(cli);
    else if (strlen(uuid) == 36)
        list_sub_by_team(data, cli, uuid);
    else
        send_unk_team(cli, uuid);
}

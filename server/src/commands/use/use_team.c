/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

static void use_thread(char *n[4], struct client_s *cli,
    struct channel_s *channel, struct team_s *team)
{
    struct packet_server_s packet = {0};

    for (struct thread_s *th = channel->threads; th; th = th->next) {
        if (strcmp(th->uuid, n[3]) != 0)
            continue;
        cli->team = team;
        cli->channel = channel;
        cli->thread = th;
        return;
    }
    packet.command = 16;
    memcpy(packet.thread_id, n[3],
        (strlen(n[3]) > sizeof(packet.thread_id) ?
        sizeof(packet.thread_id) : strlen(n[3])));
    add_to_buffer_list(cli, packet);
}

static void use_channel(char *n[4], struct client_s *cli, struct team_s *team)
{
    struct packet_server_s packet = {0};

    for (struct channel_s *ch = team->channels; ch; ch = ch->next) {
        if (strcmp(ch->uuid, n[2]) != 0)
            continue;
        if (n[3]) {
            use_thread(n, cli, ch, team);
            return;
        }
        cli->team = team;
        cli->channel = ch;
        cli->thread = NULL;
        return;
    }
    packet.command = 15;
    memcpy(packet.thread_id, n[2],
        (strlen(n[2]) > sizeof(packet.thread_id) ?
            sizeof(packet.thread_id) : strlen(n[2])));
    add_to_buffer_list(cli, packet);
}

void use_team(char *n[4], data_server_t *data, struct client_s *cli)
{
    struct packet_server_s packet = {0};

    for (struct team_s *teams = data->l_teams; teams; teams = teams->next) {
        if (strcmp(teams->uuid, n[1]) != 0)
            continue;
        if (n[2]) {
            use_channel(n, cli, teams);
            return;
        }
        cli->team = teams;
        cli->channel = NULL;
        cli->thread = NULL;
        return;
    }
    packet.command = 14;
    memcpy(packet.thread_id, n[1],
        (strlen(n[3]) > sizeof(packet.thread_id) ?
            sizeof(packet.thread_id) : strlen(n[1])));
    add_to_buffer_list(cli, packet);
}
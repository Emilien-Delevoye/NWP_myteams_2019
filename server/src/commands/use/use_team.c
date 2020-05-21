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
    char buffer[BF_S] = {0};

    for (struct thread_s *th = channel->threads; th; th = th->next) {
        if (strcmp(th->uuid, n[3]) != 0)
            continue;
        cli->team = team;
        cli->channel = channel;
        cli->thread = th;
        return;
    }
    strcpy(buffer, "client_error_unknown_thread|");
    strcat(buffer, n[3]);
    add_to_buffer_list(cli, buffer);
}

static void use_channel(char *n[4], struct client_s *cli, struct team_s *team)
{
    char buffer[BF_S] = {0};

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
    strcpy(buffer, "client_error_unknown_channel|");
    strcat(buffer, n[2]);
    add_to_buffer_list(cli, buffer);
}

void use_team(char *n[4], data_server_t *data, struct client_s *cli)
{
    char buffer[BF_S] = {0};

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
    strcpy(buffer, "client_error_unknown_team|");
    strcat(buffer, n[1]);
    add_to_buffer_list(cli, buffer);
}
/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>

void send_unk_team(struct client_s *cli, char *uuid)
{
    struct packet_server_s packet = {0};
    size_t len_uuid = strlen(uuid);
    size_t len_id = sizeof(packet.team_id);

    packet.command = 14;
    memcpy(packet.team_id, uuid, (len_uuid > len_id ? len_id : len_uuid));
    add_to_buffer_list(cli, packet);
}

static void remove_use(struct client_s *cli, const struct list_team_cli_s *c,
    short counter)
{
    struct packet_server_s packet = {0};

    if (cli->team == c->team) {
        cli->team = NULL;
        cli->channel = NULL;
        cli->thread = NULL;
    }
    if (counter == 1) {
        packet.command = 29;
        strcpy(packet.user_id, cli->user->uuid);
        strcpy(packet.team_id, c->team->uuid);
        add_to_buffer_list(cli, packet);
    }
}

void unsubscribe_fct(char *uuid, struct client_s *cli, short *counter)
{
    struct list_team_cli_s *prev = NULL;

    for (struct list_team_cli_s *c = cli->user->joined_teams; c; c = c->next) {
        if (strcmp(uuid, c->team->uuid) == 0) {
            if (!prev)
                cli->user->joined_teams = c->next;
            else
                prev->next = c->next;
            ++(*counter);
            remove_use(cli, c, *counter);
            unsubscribe_fct(uuid, cli, counter);
            free(c);
            return;
        }
        prev = cli->user->joined_teams;
    }
    if (*counter == 0)
        send_unk_team(cli, uuid);
}

void unsubscribe(char buffer[BF_S], data_server_t *data, struct client_s *cli)
{
    char *sep = "|";
    char *create[4] = {NULL, NULL, NULL, NULL};
    short counter = 0;

    create[0] = strtok(buffer, sep);
    create[1] = strtok(NULL, sep);
    if (create[1])
        unsubscribe_fct(create[1], cli, &counter);
    (void)data;
}
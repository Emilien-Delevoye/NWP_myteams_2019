/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <unistd.h>

static void ping_client_n_team(struct team_s *new, struct client_s *cli)
{
    char buffer[BF_S] = {0};

    strcpy(buffer, "n_team|");
    strcpy(buffer + 7, (const char *)new->uuid);
    strcpy(buffer + 7 + sizeof(new->uuid), "|");
    strcpy(buffer + 8 + sizeof(new->uuid), new->name);
    strcpy(buffer + 8 + sizeof(new->uuid) + sizeof(new->name), "|");
    strcpy(buffer + 9 + sizeof(new->uuid) + sizeof(new->name), new->desc);
    write(1, buffer, BF_S);
    add_to_buffer_list(cli, buffer);
}

void init_team(char *n[3], struct team_s *new, struct client_s *cli)
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
/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <unistd.h>

bool existing_team(char *name, struct team_s *list, struct client_s *cli)
{
    char buffer_error[BF_S] = {0};

    if (!list)
        return (false);
    while (list) {
        if (strcmp(name, list->name) == 0) {
            strcpy(buffer_error, "already_exit");
            add_to_buffer_list(cli, buffer_error);
            return (true);
        }
        list = list->next;
    }
    return (false);
}

static void ping_client_n_team(struct team_s *new, struct client_s *cli,
    data_server_t *data)
{
    char buffer[BF_S] = {0};

    strcpy(buffer, "n_team|");
    strcpy(buffer + 7, (const char *)new->uuid);
    strcpy(buffer + 7 + sizeof(new->uuid), "|");
    strcpy(buffer + 8 + sizeof(new->uuid), new->name);
    strcpy(buffer + 8 + sizeof(new->uuid) + sizeof(new->name), "|");
    strcpy(buffer + 9 + sizeof(new->uuid) + sizeof(new->name), new->desc);
    strcpy(buffer + 9 + sizeof(new->uuid) + sizeof(new->name) +
        sizeof(new->desc), "|");
    add_to_broadcast_list(data, buffer, NULL);
}

void init_team(char *n[3], struct team_s *new, struct client_s *cli,
    data_server_t *data)
{
    size_t len_1 = strlen(n[1]);
    size_t len_2 = strlen(n[2]);
    uuid_t uuid;

    memset(new, 0, sizeof(struct team_s));
    strncpy(new->name, n[1], (len_1 > 32 ? 32 : len_1));
    strncpy(new->desc, n[2], (len_2 > 255 ? 255 : len_2));
    uuid_generate_random(uuid);
    uuid_unparse(uuid, new->uuid);
    server_event_team_created(U_TC new->uuid, new->name, U_TC cli->user->uuid);
    ping_client_n_team(new, cli, data);
    new->next = NULL;
}
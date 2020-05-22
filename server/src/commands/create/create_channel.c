/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <unistd.h>

bool existing_channel(char *name, struct channel_s *list, struct client_s *cli)
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

static void ping_client_n_channel(struct channel_s *new, struct client_s *cli)
{
    char buffer[BF_S] = {0};

    strcpy(buffer, "n_channel|");
    strcpy(buffer + 7, (const char *)new->uuid);
    strcpy(buffer + 7 + sizeof(new->uuid), "|");
    strcpy(buffer + 8 + sizeof(new->uuid), new->name);
    strcpy(buffer + 8 + sizeof(new->uuid) + sizeof(new->name), "|");
    strcpy(buffer + 9 + sizeof(new->uuid) + sizeof(new->name), new->desc);
    write(1, buffer, BF_S);
    add_to_buffer_list(cli, buffer);
}

void init_channel(char *n[3], struct channel_s *new,
    struct client_s *cli)
{
    size_t len_1 = strlen(n[1]);
    size_t len_2 = strlen(n[2]);
    uuid_t uuid;

    memset(new, 0, sizeof(struct channel_s));
    strncpy(new->name, n[1], (len_1 > 32 ? 32 : len_1));
    strncpy(new->desc, n[2], (len_2 > 255 ? 255 : len_2));
    uuid_generate_random(uuid);
    uuid_unparse(uuid, new->uuid);
    server_event_channel_created(U_TC cli->team->uuid, U_TC new->uuid,
        new->name);
    ping_client_n_channel(new, cli);
    new->next = NULL;
}
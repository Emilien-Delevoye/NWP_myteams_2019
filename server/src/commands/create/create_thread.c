/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

bool existing_thread(char *name, struct thread_s *list, struct client_s *cli)
{
    struct packet_server_s packet = {0};

    if (!list)
        return (false);
    while (list) {
        if (strcmp(name, list->name) == 0) {
            packet.command = 19;
            add_to_buffer_list(cli, packet);
            return (true);
        }
        list = list->next;
    }
    return (false);
}

static void ping_client_n_thread(struct thread_s *new, struct client_s *cli,
    data_server_t *data)
{
    struct packet_server_s packet = {0};

    packet.command = 7;
    memcpy(packet.thread_id, new->uuid, sizeof(new->uuid));
    memcpy(packet.user_id, cli->user->uuid, sizeof(packet.user_id));
    memcpy(packet.name, new->name, sizeof(new->name));
    memcpy(packet.body, new->msg, sizeof(new->msg));
    packet.time_stamp = new->timestamp;
    add_to_broadcast_list(data, packet, NULL);
    packet.command = 26;
    add_to_buffer_list(cli, packet);
}

void init_thread(char *n[3], struct thread_s *new,
    struct client_s *cli, data_server_t *data)
{
    size_t len_1 = strlen(n[1]);
    size_t len_2 = strlen(n[2]);
    uuid_t uuid;

    memset(new, 0, sizeof(struct thread_s));
    strncpy(new->name, n[1], (len_1 > 32 ? 32 : len_1));
    strncpy(new->msg, n[2], (len_2 > 512 ? 512 : len_2));
    new->timestamp = time(NULL);
    new->comments = NULL;
    new->next = NULL;
    uuid_generate_random(uuid);
    uuid_unparse(uuid, new->uuid);
    server_event_thread_created(cli->channel->uuid, new->uuid, cli->user->uuid,
        new->msg);
    ping_client_n_thread(new, cli, data);
    new->next = NULL;
}
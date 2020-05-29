/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>

static void send_unauthorized(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    packet.command = 18;
    add_to_buffer_list(cli, packet);
}

static void send_event(data_server_t *data, struct user_s *usr,
    struct packet_server_s packet)
{
    for (struct client_s *cli = data->l_clients; cli; cli = cli->next) {
        if (cli->user == usr)
            add_to_buffer_list(cli, packet);
    }
}

static void add_to_user(struct user_s *usr, struct packet_server_s packet,
    struct client_s *cli)
{
    struct list_msg_cli_s *new = malloc(sizeof(struct list_msg_cli_s));
    struct list_msg_cli_s *cur = usr->msg;

    if (!new)
        return;
    memset(new, 0, sizeof(struct list_msg_cli_s));
    strcpy(new->uuid_rx, packet.team_id);
    strcpy(new->uuid_tx, packet.user_id);
    strcpy(new->msg, packet.body);
    new->next = NULL;
    new->timestamp = packet.time_stamp;
    if (!cur) {
        usr->msg = new;
    } else {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    }
    add_to_current_usr(packet, cli);
}

static void add_message_to_user(char uuid[LUID], data_server_t *data,
    char msg[513], struct client_s *cli)
{
    struct packet_server_s packet = {0};

    packet.command = 3;
    memcpy(packet.user_id, cli->user->uuid, sizeof(packet.user_id));
    memcpy(packet.team_id, uuid, sizeof(packet.team_id));
    memcpy(packet.body, msg, sizeof(packet.body));
    packet.time_stamp = time(NULL);
    for (struct user_s *cur = data->l_users; cur; cur = cur->next) {
        if (strcmp(cur->uuid, uuid) == 0) {
            server_event_private_message_sended(cli->user->uuid, uuid, msg);
            add_to_user(cur, packet, cli);
            send_event(data, cur, packet);
            return;
        }
    }
    packet.command = 17;
    add_to_buffer_list(cli, packet);
}

void send_cmd(char buffer[BF_S], data_server_t *data, struct client_s *client)
{
    char *cr[3] = {NULL, NULL, NULL};
    char uuid[LUID] = {0};
    char ms[513] = {0};
    size_t len_cr2;

    cr[0] = strtok(buffer, "|");
    cr[1] = strtok(NULL, "|");
    cr[2] = strtok(NULL, "|");
    if (!cr[1] || !cr[2] || strlen(cr[1]) != (LUID - 1)) {
        send_unauthorized(client);
        return;
    }
    len_cr2 = strlen(cr[2]);
    memcpy(uuid, cr[1], LUID - 1);
    memcpy(ms, cr[2], (len_cr2 > sizeof(ms) ? sizeof(ms) : len_cr2));
    add_message_to_user(uuid, data, ms, client);
}
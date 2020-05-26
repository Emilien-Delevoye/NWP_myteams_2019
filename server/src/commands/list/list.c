/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

static void list_teams(data_server_t *data, struct client_s *cli)
{
    struct packet_server_s packet = {0};

    for (struct team_s *cur = data->l_teams; cur; cur = cur->next) {
        memset(&packet, 0, sizeof(packet));
        packet.command = 9;
        memcpy(packet.team_id, cur->uuid, sizeof(packet.team_id));
        memcpy(packet.name, cur->name, sizeof(cur->name));
        memcpy(packet.description, cur->desc, sizeof(cur->desc));
        add_to_buffer_list(cli, packet);
    }
}

static void list_channels(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    for (struct channel_s *cha = cli->team->channels; cha; cha = cha->next) {
        memset(&packet, 0, sizeof(packet));
        packet.command = 10;
        memcpy(packet.channel_id, cha->uuid, sizeof(packet.channel_id));
        memcpy(packet.name, cha->name, sizeof(cha->name));
        memcpy(packet.description, cha->desc, sizeof(cha->desc));
        add_to_buffer_list(cli, packet);
    }
}

static void list_threads(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    for (struct thread_s *thr = cli->channel->threads; thr; thr = thr->next) {
        memset(&packet, 0, sizeof(packet));
        packet.command = 11;
        memcpy(packet.thread_id, thr->uuid, sizeof(thr->uuid));
        memcpy(packet.name, thr->name, sizeof(thr->name));
        memcpy(packet.user_id, thr->uuid_user, sizeof(thr->uuid_user));
        memcpy(&packet.time_stamp, &thr->timestamp, sizeof(thr->timestamp));
        memcpy(packet.body, thr->msg, sizeof(thr->msg));
        add_to_buffer_list(cli, packet);
    }
}

static void list_reply(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    for (struct comment_s *com = cli->thread->comments; com; com = com->next) {
        memset(&packet, 0, sizeof(packet));
        packet.command = 12;
        memcpy(packet.thread_id, cli->thread->uuid, sizeof(cli->thread->uuid));
        memcpy(packet.user_id, com->uuid_user, sizeof(packet.user_id));
        memcpy(&packet.time_stamp, &com->timestamp, sizeof(packet.time_stamp));
        memcpy(packet.body, com->body, sizeof(com->body));
        add_to_buffer_list(cli, packet);
    }
}

void list(char buffer[BF_S] __attribute__((unused)), data_server_t *data,
    struct client_s *cli)
{
    if (!cli->team)
        list_teams(data, cli);
    if (cli->team && !cli->channel)
        list_channels(cli);
    if (cli->team && cli->channel && !cli->thread)
        list_threads(cli);
    if (cli->team && cli->channel && cli->thread)
        list_reply(cli);
}
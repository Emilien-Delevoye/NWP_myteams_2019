/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

void info_user(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    memset(&packet, 0, sizeof(packet));
    packet.command = 20;
    memcpy(packet.user_id, cli->user->uuid, sizeof(packet.user_id));
    memcpy(packet.name, cli->user->username, sizeof(cli->user->username));
    packet.user_status = 1;
    add_to_buffer_list(cli, packet);
}

void info_team(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    memset(&packet, 0, sizeof(packet));
    packet.command = 21;
    memcpy(packet.team_id, cli->team->uuid, sizeof(cli->team->name));
    memcpy(packet.name, cli->team->name, sizeof(cli->team->name));
    memcpy(packet.description, cli->team->desc, sizeof(cli->team->desc));
    add_to_buffer_list(cli, packet);
}

void info_channel(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    memset(&packet, 0, sizeof(packet));
    packet.command = 22;
    memcpy(packet.channel_id, cli->channel->uuid, sizeof(cli->channel->uuid));
    memcpy(packet.name, cli->channel->name, sizeof(cli->channel->name));
    memcpy(packet.description, cli->channel->desc, sizeof(cli->channel->desc));
    add_to_buffer_list(cli, packet);
}

void info_thread(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    memset(&packet, 0, sizeof(packet));
    packet.command = 23;
    memcpy(packet.thread_id, cli->thread->uuid, sizeof(cli->thread->uuid));
    memcpy(packet.user_id, cli->thread->uuid_user,
        sizeof(cli->thread->uuid_user));
    memcpy(&packet.time_stamp, &cli->thread->timestamp,
        sizeof(cli->thread->timestamp));
    memcpy(packet.name, cli->thread->name, sizeof(cli->thread->name));
    memcpy(packet.body, cli->thread->msg, sizeof(cli->thread->msg));
    add_to_buffer_list(cli, packet);
}

void info(char buffer[BF_S] __attribute__((unused)),
    data_server_t *data __attribute__((unused)), struct client_s *cli)
{
    if (!cli->team)
        info_user(cli);
    if (cli->team && !cli->channel)
        info_team(cli);
    if (cli->team && cli->channel && !cli->thread)
        info_channel(cli);
    if (cli->team && cli->channel && cli->thread)
        info_thread(cli);
}

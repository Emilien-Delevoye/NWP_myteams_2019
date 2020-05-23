/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void (*rx_server[])(struct packet_server_s, struct client_s *) =
{
    event_loggedin,
    event_loggedout,
    event_pv_mes_rx,
    event_th_mes_rx,
    event_team_created,
    event_channel_created,
    event_thread_created,
    print_users,
    print_teams,
    team_print_channels,
    channel_print_threads,
    thread_print_replies,
    pv_msg_print_msg,
    error_unk_team,
    error_unk_channel,
    error_unk_thread,
    error_unk_user,
    error_unauthorized,
    error_already_exist,
    print_user,
    print_team,
    print_channel,
    print_thread,
    print_team_created,
    print_channel_created,
    print_thread_created,
    print_reply_created,
    print_client_subscribed,
    print_client_unsubscribed
};

void read_input(struct client_s *client)
{
    char **cmd = NULL;
    char *buffer = NULL;
    size_t len = 0;
    ssize_t val_getline = getline(&buffer, &len, stdin);

    if (val_getline <= 0) {
        client->server_running = false;
        return;
    }
    cmd = parsing(buffer);
    call_function(client, cmd);
    free_cmd(cmd);
}

void read_server(struct client_s *client)
{
    struct packet_server_s packet = {0};
    int size_read = read(client->sckt, &packet, sizeof(packet));

    if (size_read == 0) {
        client->server_running = false;
        puts(RED"[STOP] Server is closed"DEFAULT);
        return;
    }
    if (packet.command == 0 || packet.command > sizeof(rx_server))
        return;
    rx_server[packet.command - 1](packet, client);
}
/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"

void logout(char buffer[BF_S] __attribute__((unused)), data_server_t *data,
            struct client_s *client)
{
    char out_buf[BF_S] = {0};

    if (!client->user)
        return;
    server_event_user_logged_out((const char *)client->user->uuid);
    create_log_buffer(out_buf, client->user, "logout");
    add_to_buffer_list(client, out_buf);
    out_buf[0] = 'b';
    add_to_broadcast_list(data, out_buf, client);
    client->user = NULL;
}
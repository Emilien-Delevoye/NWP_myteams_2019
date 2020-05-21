/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>

void create_server_cli(char read_buf[BF_S], struct client_s *cli)
{
    char uuid[LUID] = {0};
    char team_name[33] = {0};
    char desc[512] = {0};

    (void)cli;
    if (strncmp("n_team", read_buf, 6) == 0) {
        memcpy(uuid, read_buf + 7, sizeof(uuid) - 1);
        memcpy(team_name, read_buf + 7 + sizeof(uuid), sizeof(team_name) - 1);
        memcpy(desc, read_buf + 7 + sizeof(uuid) + sizeof(team_name),
            sizeof(desc));
        client_event_team_created(uuid, team_name, desc);
    }
}
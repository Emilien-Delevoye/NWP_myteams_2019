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

void read_input(struct client_s *client)
{
    char **cmd = NULL;
    char *buffer = NULL;
    size_t len = 0;

    getline(&buffer, &len, stdin);
    cmd = parsing(buffer);
    call_function(client, cmd);
    free_cmd(cmd);
}

void read_server(struct client_s *client)
{
    char buffer[4096] = {0};
    int size_read = read(client->sckt, buffer, sizeof(buffer));

    if (size_read == 0) {
        client->server_running = false;
        puts(RED"[STOP] Server is closed"DEFAULT);
        return;
    }
    printf("Buffer read : %s\n", buffer);
}
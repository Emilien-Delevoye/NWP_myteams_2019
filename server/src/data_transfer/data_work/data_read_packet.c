/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void read_buffer(char buffer[4096],
    data_server_t *data __attribute__((unused)), struct client_s *cur)
{
    char to_write[4096] = {0};

    printf(YELLOW"[INFO] New packet : %s\n"DEFAULT, buffer);
    strcpy(to_write, "Message receive");
    write(cur->client_sckt, to_write, 4096);
}
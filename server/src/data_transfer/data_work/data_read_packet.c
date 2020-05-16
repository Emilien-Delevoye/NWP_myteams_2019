/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>
#include <string.h>

void read_buffer(char buffer[BF_S],
    data_server_t *data __attribute__((unused)), struct client_s *cur)
{
    char to_write[BF_S] = {0};

    printf(YELLOW"[INFO] New packet : %s\n"DEFAULT, buffer);
    strcpy(to_write, "Message receive");
    add_to_buffer_list(cur, to_write);
}
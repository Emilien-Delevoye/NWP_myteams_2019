/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>

void read_buffer(char buffer[BF_S], data_server_t *data, struct client_s *cur)
{
    interpret_cmd(buffer, data, cur);
}
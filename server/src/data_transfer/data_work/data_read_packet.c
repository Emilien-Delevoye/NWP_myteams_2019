/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>

void read_buffer(char buffer[4096],
    data_server_t *data __attribute__((unused)))
{
    printf(YELLOW"[INFO] New packet : %s\n"DEFAULT, buffer);
}
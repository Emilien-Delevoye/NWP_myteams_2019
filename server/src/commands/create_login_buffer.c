/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

void create_log_buffer(char buffer[BF_S], struct user_s *cur, char *cmd)
{
    size_t len = strlen(cmd);

    memset(buffer, 0, BF_S);
    for (size_t a = 0; a < len; ++a)
        buffer[a] = cmd[a];
    buffer[len] = ' ';
    for (size_t a = 0; a < sizeof(cur->uuid); ++a)
        buffer[a + (len + 1)] = (char)cur->uuid[a];
    buffer[(len + 1) + sizeof(cur->uuid)] = ' ';
    for (size_t a = 0; a < strlen(cur->username); ++a)
        buffer[(len + 2) + sizeof(cur->uuid) + a] = cur->username[a];
}
/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

void create_login_buffer(char buffer[BF_S], struct user_s *cur)
{
    char *login = "login";

    memset(buffer, 0, BF_S);
    for (int a = 0; a < 5; ++a)
        buffer[a] = login[a];
    buffer[5] = ' ';
    for (size_t a = 0; a < sizeof(cur->uuid); ++a)
        buffer[a + 6] = (char)cur->uuid[a];
    buffer[6 + sizeof(cur->uuid)] = ' ';
    for (size_t a = 0; a < strlen(cur->username); ++a)
        buffer[7 + sizeof(cur->uuid) + a] = cur->username[a];
}
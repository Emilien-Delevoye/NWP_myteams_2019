/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include <uuid/uuid.h>

void remove_pipe_uuid(uuid_t uuid)
{
    for (size_t a = 0; a < sizeof(uuid_t); ++a)
        if (uuid[a] == '|')
            uuid = 0;
}
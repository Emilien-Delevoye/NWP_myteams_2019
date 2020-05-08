/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool not_valid_command(const char *buf)
{
    int quotes = 0;
    bool not_valid = false;

    if (!buf || buf[0] != '/' || strncmp(buf, "/use", 4) != 0)
        not_valid = true;
    for (int a = 0; buf[a]; ++a) {
        quotes = (buf[a] == '\"' ? quotes + 1 : quotes);
        if (DOMINIQUE)
            not_valid = true;
    }
    if (quotes % 2 != 0)
        not_valid = true;
    if (not_valid)
        printf(RED"Invalid command : %s"DEFAULT, buf);
    return (not_valid);
}

int get_nb_arg(const char *buffer)
{
    int counter = 0;

    for (int a = 0; buffer[a]; ++a)
        if (buffer[a] == '\"')
            ++counter;
    return ((counter / 2));
}

char *get_cmd(char **buffer)
{
    char *output = NULL;
    size_t len = 0;

    for (int a = 0; (*buffer)[a] && (*buffer)[a] != ' ' &&
        (*buffer)[a] != '\"'; ++a)
        ++len;
    output = malloc(len + 1);
    if (!output)
        return (NULL);
    for (size_t a = 0; a < len; ++a)
        output[a] = (*buffer)[a];
    output[len] = 0;
    *buffer += len;
    return (output);
}

char *get_arg(char **buffer)
{
    size_t len_arg = 0;
    char *output;

    while (**buffer != '\"')
        ++(*buffer);
    ++(*buffer);
    while ((*buffer)[len_arg] != '\"' && (*buffer)[len_arg] != 0)
        ++len_arg;
    output = malloc(len_arg + 1);
    for (size_t a = 0; a < len_arg; ++a)
        output[a] = (*buffer)[a];
    output[len_arg] = 0;
    (*buffer) += (len_arg + 1);
    return (output);
}

void free_cmd(char **cmd)
{
    if (!cmd)
        return;
    for (int a = 0; cmd[a]; ++a)
        free(cmd[a]);
    free(cmd);
}
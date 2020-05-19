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

const char *tab_commands[30] = {"/use", "/login", "/logout", "/users", "/user",
    "/send", "/messages", "/subscribe", "/subscribed", "/unsubscribe", "/use",
    "/create", "/list", "/info", NULL};

bool check_commands(const char *buf)
{
    for (int a = 0; tab_commands[a]; ++a)
        if (strncmp(buf, tab_commands[a], strlen(tab_commands[a])) == 0)
            return (true);
    return (false);
}

bool not_valid_command(const char *buf)
{
    int quotes = 0;
    bool not_valid = false;

    if (!buf || buf[0] != '/' || !check_commands(buf))
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
    for (int a = 0; output[a]; ++a)
        if (output[a] == '\n')
            output[a] = 0;
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
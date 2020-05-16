/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>
#include <stdlib.h>

void free_cmd(char **cmd)
{
    if (!cmd)
        return;
    for (int a = 0; cmd[a]; ++a)
        free(cmd[a]);
    free(cmd);
}

char **pars_alloc_tab(char *buffer)
{
    int nb_args = get_nb_arg(buffer);
    char **output = malloc(sizeof(char *) * (nb_args + 2));

    if (!output)
        return (NULL);
    output[nb_args + 1] = NULL;
    output[0] = get_cmd(&buffer);
    for (int a = 1; a != nb_args + 1; ++a)
        output[a] = get_arg(&buffer);
    return (output);
}

char **parsing(char *buffer)
{
    char **output;

    if (not_valid_command(buffer))
        return (NULL);
    output = pars_alloc_tab(buffer);
    return (output);
}
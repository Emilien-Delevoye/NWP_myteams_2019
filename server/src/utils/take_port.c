/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include <stdio.h>
#include <stdbool.h>

static bool check_num_str(const char *str)
{
    for (int a = 0; str[a]; ++a)
        if (str[a] < '0' || str[a] > '9')
            return (false);
    return (true);
}

int take_port(char const *port_str)
{
    int port = 0;

    if (!check_num_str(port_str) || !sscanf(port_str, "%d", &port))
        return (-1);
    return (port);
}
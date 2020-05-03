/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include <stdio.h>

int take_port(char const *port_str)
{
    int port;

    if (!sscanf(port_str, "%d", &port)) {
        puts("Port error");
        return (84);
    }
    printf("En attente de connexion sur le port : %d\n", port);
    return (port);
}
/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#ifndef MYTEAMS_CLIENT_H
#define MYTEAMS_CLIENT_H

//Functions
int take_port(char const *port_str);
int connect_client(const char *ip, int port);

//Structures
struct client_s {
    int sckt;
};

#endif

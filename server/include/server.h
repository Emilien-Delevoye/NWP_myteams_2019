/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#ifndef MYTEAMS_SERVER_H
#define MYTEAMS_SERVER_H

#include <stdbool.h>

/* *** Function definition *** */
int take_port(char const *);
int init_ctr_socket(int port);
bool server_running(void);
int setup_sigcatch(void);


/* *** Macros definition *** */


/* *** Structures definition *** */



#endif

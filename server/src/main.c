/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include <stdio.h>

void help(void)
{
    puts("USAGE: ./myteams_server port\n"
         "\tport\tis the port number on which the server socket listens.\n");
}

int main(int ac, char **av __attribute__((unused)))
{
    if (ac != 2) {
        help();
        return (84);
    }
    return (0);
}
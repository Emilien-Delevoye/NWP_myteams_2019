/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include <stdio.h>

void help(void)
{
    puts("USAGE: ./myteams_cli ip port\n\t"
        "ip\tis the server ip address on which the server socket listens\n\t"
        "port\tis the port number on which the server socket listens\n");
}

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
    if (ac != 3) {
        help();
        return (84);
    }
    return (0);
}
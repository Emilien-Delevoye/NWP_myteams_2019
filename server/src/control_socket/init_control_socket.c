/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

const int nb_connections = 5;

static void setup_port(struct sockaddr_in *serv_addr, int port)
{
    memset(serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr->sin_addr.s_addr = INADDR_ANY;
    serv_addr->sin_port = htons(port);
    serv_addr->sin_family = AF_INET;
}

static int start_listening(int fd, struct sockaddr *serv_addr)
{
    if (bind(fd, serv_addr, sizeof(struct sockaddr)) < 0) {
        printf("bind: %s\n", strerror(errno));
        return (-1);
    }
    if (listen(fd, nb_connections) < 0) {
        printf("listen: %s\n", strerror(errno));
        return (-1);
    }
    return (0);
}

int init_ctr_socket(int port)
{
    int fd;
    int opt = 1;
    struct sockaddr_in serv_addr;

    if (port <= 0)
        return (-1);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        puts("socket init failed");
        return (-1);
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        return (84);
    setup_port(&serv_addr, port);
    if (start_listening(fd, (struct sockaddr *)&serv_addr) < 0)
        return (-1);
    printf("Listening for connections on port: %d\n", port);
    return (fd);
}
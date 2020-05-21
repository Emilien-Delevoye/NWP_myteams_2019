/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int connect_client(const char *ip, int port)
{
    struct sockaddr_in servaddr;
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0)
        return (-1);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip);
    if (connect(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        printf("connect: %s\n", strerror(errno));
        return (-1);
    }
    printf("fd : %d\n", fd);
    printf("Connected to %s:%d\n", ip, port);
    return (fd);
}
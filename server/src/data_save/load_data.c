/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <fcntl.h>
#include <unistd.h>

static char get_ctrl(int fd, char *ctrl)
{
    int len = read(fd, ctrl, 1);

    if (len != 1)
        return (0);
    return (*ctrl);
}

void load_data(data_server_t *data __attribute__((unused)))
{
    int fd = open("domain.save", O_RDONLY);
    struct load_data_s load_data = {0};
    char ctrl;

    if (fd < 0)
        return;
    while (get_ctrl(fd, &ctrl) != 0) {
        if (ctrl == '1')
            load_user(fd, &load_data);
        else if (ctrl == '2')
            load_joined_team(fd, &load_data);
        else
            load_team(fd, &load_data);
    }
}
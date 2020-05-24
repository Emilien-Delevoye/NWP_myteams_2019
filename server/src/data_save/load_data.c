/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <fcntl.h>
#include <unistd.h>

const char value_load[10] = "1234567890";

static void (*fct[])(int, struct load_data_s *) =
{
    load_user, load_joined_team, load_team, load_channel, load_thread,
    load_comment, NULL
};

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
    while (get_ctrl(fd, &ctrl) != 0)
        for (int a = 0; a < sizeof(value_load); ++a)
            if (ctrl == value_load[a] && fct[a])
                fct[a](fd, &load_data);
}
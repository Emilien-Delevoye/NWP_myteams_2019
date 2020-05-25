/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char value_load[10] = "1234567890";

static void (*fct[])(int, struct load_data_s *) =
{
    load_user, load_joined_team, load_team, load_channel, load_thread,
    load_comment, NULL
};

static char get_ctrl(int fd, char ctrl[1])
{
    int len = read(fd, ctrl, 1);

    if (len != 1)
        return (0);
    return (*ctrl);
}

void add_user_data(data_server_t *data, struct l_save_user_s cur)
{
    struct user_s *new = malloc(sizeof(struct user_s));
    struct user_s *cur_list = data->l_users;

    if (!new)
        return;
    memcpy(new->username, cur.user.username, sizeof(new->username));
    memcpy(new->uuid, cur.user.uuid, sizeof(new->uuid));
    new->next = NULL;
    new->joined_teams = NULL;
    if (!data->l_users) {
        data->l_users = new;
    } else {
        while (cur_list->next)
            cur_list = cur_list->next;
        cur_list->next = new;
    }
}

void load_data(data_server_t *data)
{
    int fd = open("domain.save", O_RDONLY);
    struct load_data_s load_data = {0};
    char ctrl;

    if (fd < 0)
        return;
    while (get_ctrl(fd, &ctrl) != 0)
        for (size_t a = 0; a < sizeof(value_load); ++a)
            if (ctrl == value_load[a] && fct[a])
                fct[a](fd, &load_data);
    for (struct l_save_team_s *cur = load_data.team; cur; cur = cur->next)
        add_team_data(data, *cur);
    for (struct l_save_user_s *cur = load_data.user; cur; cur = cur->next)
        add_user_data(data, *cur);
    close(fd);
}
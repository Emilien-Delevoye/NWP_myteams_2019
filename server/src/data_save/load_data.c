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
    load_comment, load_message, NULL
};

static char get_ctrl(int fd, char ctrl[1])
{
    int len = read(fd, ctrl, 1);

    if (len != 1)
        return (0);
    return (*ctrl);
}

void add_join_team(data_server_t *data, char uuid[LUID], struct user_s *cur_us)
{
    struct team_s *team_to_add = NULL;
    struct list_team_cli_s *new;
    struct list_team_cli_s *current = cur_us->joined_teams;

    for (struct team_s *cur = data->l_teams; cur; cur = cur->next)
        team_to_add = (strcmp(cur->uuid, uuid) == 0 ? cur : team_to_add);
    if (!team_to_add)
        return;
    new = malloc(sizeof(struct list_team_cli_s));
    if (!new)
        return;
    new->team = team_to_add;
    new->next = NULL;
    if (!cur_us->joined_teams) {
        cur_us->joined_teams = new;
    } else {
        while (current->next)
            current = current->next;
        current->next = new;
    }
}

void add_msg_user(struct l_messages_s *cur,
    struct user_s *usr)
{
    struct list_msg_cli_s *new = malloc(sizeof(struct list_msg_cli_s));
    struct list_msg_cli_s *current = usr->msg;

    if (!new)
        return;
    memcpy(new->msg, cur->message.message, sizeof(new->msg));
    memcpy(new->uuid_rx, cur->message.uuid_rx, sizeof(new->uuid_rx));
    memcpy(new->uuid_tx, cur->message.uuid_tx, sizeof(new->uuid_tx));
    memcpy(&new->timestamp, &cur->message.timestamp, sizeof(new->timestamp));
    new->next = NULL;
    if (!usr->msg) {
        usr->msg = new;
    } else {
        while (current->next)
            current = current->next;
        current->next = new;
    }
}

void add_user_data(data_server_t *data, struct l_save_user_s cur)
{
    struct user_s *new = malloc(sizeof(struct user_s));
    struct user_s *current;

    if (!new)
        return;
    memcpy(new->username, cur.user.username, sizeof(new->username));
    memcpy(new->uuid, cur.user.uuid, sizeof(new->uuid));
    new->next = NULL;
    new->joined_teams = NULL;
    new->msg = NULL;
    if (!data->l_users) {
        data->l_users = new;
    } else {
        for (current = data->l_users; current->next; current = current->next);
        current->next = new;
    }
    for (struct l_joi_team_s *l_joi = cur.joined; l_joi; l_joi = l_joi->next)
        add_join_team(data, l_joi->joined.uuid, new);
    for (struct l_messages_s *l_msg = cur.msg; l_msg; l_msg = l_msg->next)
        add_msg_user(l_msg, new);
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
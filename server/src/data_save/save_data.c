/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void save_joined_teams(struct user_s *us, int fd)
{
    struct joi_team_s joined_list;

    for (struct list_team_cli_s *cu = us->joined_teams; cu; cu = cu->next) {
        memset(&joined_list, 0, sizeof(struct joi_team_s));
        memcpy(&joined_list.uuid, cu->team->uuid, sizeof(joined_list.uuid));
        write(fd, "2", 1);
        write(fd, &joined_list, sizeof(joined_list));
    }
}

void save_pv_messages(struct user_s *us, int fd)
{
    struct save_message_s message;

    for (struct list_msg_cli_s *cur = us->msg; cur; cur = cur->next) {
        memset(&message, 0, sizeof(message));
        memcpy(message.uuid_send, cur->uuid_sender, sizeof(cur->uuid_sender));
        memcpy(message.message, cur->msg, sizeof(cur->msg));
        memcpy(&message.timestamp, &cur->timestamp, sizeof(cur->timestamp));
        write(fd, "7", 1);
        write(fd, &message, sizeof(message));
    }
}

void save_user(data_server_t data, int fd)
{
    struct save_user_s save_user;

    for (struct user_s *cur = data.l_users; cur; cur = cur->next) {
        memset(&save_user, 0, sizeof(save_user));
        memcpy(&save_user.username, cur->username, sizeof(cur->username));
        memcpy(&save_user.uuid, cur->uuid, sizeof(cur->uuid));
        write(fd, "1", 1);
        write(fd, &save_user, sizeof(save_user));
        save_joined_teams(cur, fd);
        save_pv_messages(cur, fd);
    }
}

void save_data(data_server_t data)
{
    int fd = open("domain.save", O_WRONLY | O_CREAT, 0666);

    if (fd < 0)
        return;
    save_user(data, fd);
    save_team(data, fd);
    close(fd);
}
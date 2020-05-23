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

struct save_user_s
{
    char username[32];
    char uuid[LUID];
};

struct save_joined_team_user_s
{
    char uuid[LUID];
};

struct save_team_s
{
    char name[33];
    char description[256];
    char uuid[LUID];
};

struct save_channel_s
{
    char name[33];
    char description[256];
    char uuid[LUID];
};

struct save_thread_s
{
    char name[33];
    char msg[513];
    char uuid[LUID];
    time_t timestamp;
};

struct save_comment_s
{
    char body[513];
};

void save_joined_teams(struct user_s *us, int fd)
{
    struct save_joined_team_user_s joined_list;

    for (struct list_team_cli_s *cu = us->joined_teams; cu; cu = cu->next) {
        write(fd, "2", 1);
        memset(&joined_list, 0, sizeof(struct save_joined_team_user_s));
        memcpy(&joined_list.uuid, cu->team->uuid, sizeof(joined_list.uuid));
        write(fd, &joined_list, sizeof(joined_list));
    }
}

void save_user(data_server_t data, int fd)
{
    struct save_user_s save_user;

    for (struct user_s *cur = data.l_users; cur; cur = cur->next) {
        memset(&save_user, 0, sizeof(save_user));
        memcpy(&save_user.username, cur->username, sizeof(cur->username));
        memcpy(&save_user.uuid, cur->uuid, sizeof(cur->uuid));
        write(fd, &save_user, sizeof(save_user));
        save_joined_teams(cur, fd);
        write(fd, "1", 1);
    }
}

void save_data(data_server_t data)
{
    int fd = open("domain.save", O_WRONLY | O_CREAT, 0666);

    if (fd < 0)
        return;
    save_user(data, fd);
    close(fd);
}

//Teams
//Channels
//Threads
//Comments
//Privates messages
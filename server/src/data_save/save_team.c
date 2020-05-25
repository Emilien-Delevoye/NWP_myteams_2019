/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <unistd.h>

static void save_comments(struct thread_s *thread, int fd)
{
    struct save_comment_s save_comment;

    for (struct comment_s *cur = thread->comments; cur; cur = cur->next) {
        memset(&save_comment, 0, sizeof(struct save_comment_s));
        memcpy(&save_comment.body, cur->body, sizeof(cur->body));
        memcpy(&save_comment.timestamp, &cur->timestamp,
            sizeof(cur->timestamp));
        write(fd, "6", 1);
        write(fd, &save_comment, sizeof(save_comment));
    }
}

static void save_thread(struct channel_s *channel, int fd)
{
    struct save_thread_s save_thread = {0};

    for (struct thread_s *cur = channel->threads; cur; cur = cur->next) {
        memset(&save_thread, 0, sizeof(struct save_thread_s));
        memcpy(&save_thread.name, cur->name, sizeof(cur->name));
        memcpy(&save_thread.msg, cur->msg, sizeof(cur->msg));
        memcpy(&save_thread.uuid, cur->uuid, sizeof(cur->uuid));
        memcpy(&save_thread.timestamp, &cur->timestamp,
            sizeof(cur->timestamp));
        write(fd, "5", 1);
        write(fd, &save_thread, sizeof(save_thread));
        save_comments(cur, fd);
    }
}

static void save_channel(struct team_s *team, int fd)
{
    struct save_channel_s save_channel;

    for (struct channel_s *cur = team->channels; cur; cur = cur->next) {
        memset(&save_channel, 0, sizeof(struct save_channel_s));
        memcpy(&save_channel.name, cur->name, sizeof(cur->name));
        memcpy(&save_channel.description, cur->desc, sizeof(cur->desc));
        memcpy(&save_channel.uuid, cur->uuid, sizeof(cur->uuid));
        write(fd, "4", 1);
        write(fd, &save_channel, sizeof(save_channel));
        save_thread(cur, fd);
    }
}

void save_team(data_server_t data, int fd)
{
    struct save_team_s save_team;

    for (struct team_s *cur = data.l_teams; cur; cur = cur->next) {
        memset(&save_team, 0, sizeof(struct save_team_s));
        memcpy(&save_team.name, cur->name, sizeof(cur->name));
        memcpy(&save_team.description, cur->desc, sizeof(cur->desc));
        memcpy(&save_team.uuid, cur->uuid, sizeof(cur->uuid));
        write(fd, "3", 1);
        write(fd, &save_team, sizeof(save_team));
        save_channel(cur, fd);
    }
}
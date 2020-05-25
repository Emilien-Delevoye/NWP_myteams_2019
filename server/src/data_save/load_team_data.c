/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>

static void add_comment_data(struct l_save_comment_s *com,
    struct thread_s *cur_thr)
{
    struct comment_s *new = malloc(sizeof(struct comment_s));
    struct comment_s *cur_list = cur_thr->comments;

    if (!new)
        return;
    memcpy(new->body, com->comment.body, sizeof(new->body));
    new->next = NULL;
    if (!cur_thr->comments) {
        cur_thr->comments = new;
    } else {
        while (cur_list->next)
            cur_list = cur_list->next;
        cur_list->next = new;
    }
}

static void add_thread_data(struct l_save_thread_s *thread,
    struct channel_s *cur_cha)
{
    struct thread_s *new = malloc(sizeof(struct thread_s));
    struct thread_s *list = NULL;

    if (!new)
        return;
    memcpy(new->name, thread->thread.name, sizeof(new->name));
    memcpy(new->msg, thread->thread.msg, sizeof(new->msg));
    memcpy(new->uuid, thread->thread.uuid, sizeof(new->uuid));
    memcpy(&new->timestamp, &thread->thread.timestamp, sizeof(new->timestamp));
    new->comments = NULL;
    new->next = NULL;
    if (!cur_cha->threads) {
        cur_cha->threads = new;
        list = new;
    } else {
        for (list = cur_cha->threads; list->next; list = list->next);
        list->next = new;
    }
    for (struct l_save_comment_s *com = thread->comments; com; com = com->next)
        add_comment_data(com, list);
}

static void add_channel_data(struct l_save_channel_s *chan,
    struct team_s *cur_team)
{
    struct channel_s *new = malloc(sizeof(struct channel_s));
    struct channel_s *cur_list = cur_team->channels;

    if (!new)
        return;
    memcpy(new->name, chan->channel.name, sizeof(new->name));
    memcpy(new->uuid, chan->channel.uuid, sizeof(new->uuid));
    memcpy(new->desc, chan->channel.description, sizeof(new->desc));
    new->next = NULL;
    new->threads = NULL;
    if (!cur_team->channels) {
        cur_team->channels = new;
        cur_list = new;
    } else {
        while (cur_list->next)
            cur_list = cur_list->next;
        cur_list->next = new;
    }
    for (struct l_save_thread_s *thr = chan->threads; thr; thr = thr->next)
        add_thread_data(thr, cur_list);
}

void add_team_data(data_server_t *data, struct l_save_team_s team)
{
    struct team_s *new = malloc(sizeof(struct team_s));
    struct team_s *cur_list = data->l_teams;

    if (!new)
        return;
    memcpy(new->name, team.team.name, sizeof(new->name));
    memcpy(new->desc, team.team.description, sizeof(new->desc));
    memcpy(new->uuid, team.team.uuid, sizeof(new->uuid));
    new->next = NULL;
    new->channels = NULL;
    if (!data->l_teams) {
        data->l_teams = new;
    } else {
        while (cur_list->next)
            cur_list = cur_list->next;
        cur_list->next = new;
    }
    for (struct l_save_channel_s *cha = team.channels; cha; cha = cha->next)
        add_channel_data(cha, new);
}

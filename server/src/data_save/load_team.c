/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <unistd.h>
#include <stdlib.h>

void add_team_to_list(struct save_team_s save_team, struct load_data_s *load)
{
    struct l_save_team_s *new = malloc(sizeof(struct l_save_team_s));
    struct l_save_team_s *current = load->team;

    if (!new)
        return;
    new->team = save_team;
    new->next = NULL;
    load->cur_team = new;
    load->cur_channel = NULL;
    load->cur_thread = NULL;
    load->cur_user = NULL;
    new->channels = NULL;
    if (!load->team) {
        load->team = new;
    } else {
        while (current->next)
            current = current->next;
        current->next = new;
    }
}

void add_joined_to_user(struct joi_team_s joined, struct load_data_s *load)
{
    struct l_joi_team_s *new = malloc(sizeof(struct l_joi_team_s));
    struct l_joi_team_s *cur;

    if (!load->user || !new || !load->cur_user)
        return;
    new->joined = joined;
    new->next = NULL;
    cur = load->cur_user->joined;
    if (!cur) {
        load->cur_user->joined = new;
    } else {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    }
}

void load_team(int fd, struct load_data_s *load_data)
{
    struct save_team_s save_team;

    if (read(fd, &save_team, sizeof(save_team)) != sizeof(save_team))
        return;
    add_team_to_list(save_team, load_data);
}

void load_joined_team(int fd, struct load_data_s *load)
{
    struct joi_team_s joined = {0};

    if (read(fd, &joined, sizeof(joined)) != sizeof(joined))
        return;
    add_joined_to_user(joined, load);
}

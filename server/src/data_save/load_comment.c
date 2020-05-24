/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <unistd.h>

static void add_to_comment_list(struct save_comment_s comment,
    struct load_data_s *load)
{
    struct l_save_comment_s *new = malloc(sizeof(struct l_save_comment_s));
    struct l_save_comment_s *current;

    if (!new || !load->cur_team || !load->cur_channel || !load->cur_thread ||
        !load->cur_team->channels || !load->cur_channel->threads)
        return;
    new->comment = comment;
    new->next = NULL;
    current = load->cur_channel->threads->comments;
    if (!load->cur_channel->threads->comments) {
        load->cur_channel->threads->comments = new;
    } else {
        while (current->next)
            current = current->next;
        current->next = new;
    }
}

void load_comment(int fd, struct load_data_s *load_data)
{
    struct save_comment_s comment;

    if (read(fd, &comment, sizeof(comment)) != sizeof(comment))
        return;
    add_to_comment_list(comment, load_data);
}
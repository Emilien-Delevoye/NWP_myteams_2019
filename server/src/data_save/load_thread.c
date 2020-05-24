/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <unistd.h>

static void add_to_thread_list(struct save_thread_s thread,
    struct load_data_s *load)
{
    struct l_save_thread_s *new = malloc(sizeof(struct l_save_thread_s));
    struct l_save_thread_s *current;

    if (!new || !load->cur_team || !load->cur_channel ||
        !load->cur_team->channels)
        return;
    new->thread = thread;
    new->comments = NULL;
    new->next = NULL;
    current = load->cur_channel->threads;
    if (!load->cur_channel->threads) {
        load->cur_channel->threads = new;
    } else {
        while (current->next)
            current = current->next;
        current->next = new;
    }
}

void load_thread(int fd, struct load_data_s *load_data)
{
    struct save_thread_s thread;

    if (read(fd, &thread, sizeof(thread)) != sizeof(thread))
        return;
    add_to_thread_list(thread, load_data);
}
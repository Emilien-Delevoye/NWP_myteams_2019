/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <unistd.h>
#include <stdlib.h>

void add_to_channel_list(struct save_channel_s chan, struct load_data_s *load)
{
    struct l_save_channel_s *new = malloc(sizeof(struct l_save_channel_s));
    struct l_save_channel_s *current;

    if (!new || !load->cur_team)
        return;
    current = load->cur_team->channels;
    new->channel = chan;
    new->threads = NULL;
    new->next = NULL;
    load->cur_channel = new;
    load->cur_thread = NULL;
    load->cur_user = NULL;
    if (!load->cur_team->channels) {
        load->cur_team->channels = new;
    } else {
        while (current->next)
            current = current->next;
        current->next = new;
    }
}

void load_channel(int fd, struct load_data_s *load_data)
{
    struct save_channel_s channel;

    if (read(fd, &channel, sizeof(channel)) != sizeof(channel))
        return;
    add_to_channel_list(channel, load_data);
}
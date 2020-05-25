/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <unistd.h>

void add_user_to_list(struct save_user_s save_user, struct load_data_s *load)
{
    struct l_save_user_s *new = malloc(sizeof(struct l_save_user_s));
    struct l_save_user_s *current = load->user;

    new->user = save_user;
    new->next = NULL;
    load->cur_user = new;
    if (!load->user) {
        load->user = new;
    } else {
        while (current->next)
            current = current->next;
        current->next = new;
    }
    server_event_user_loaded(new->user.uuid, new->user.username);
}

void load_user(int fd, struct load_data_s *load_data)
{
    struct save_user_s save_user = {0};

    if (read(fd, &save_user, sizeof(save_user)) != sizeof(save_user))
        return;
    add_user_to_list(save_user, load_data);
}

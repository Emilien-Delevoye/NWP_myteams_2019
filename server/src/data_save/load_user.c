/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <unistd.h>

void add_msg_to_user(struct l_save_user_s *user, struct save_message_s msg)
{
    struct l_messages_s *new = malloc(sizeof(struct l_messages_s));
    struct l_messages_s *cur = user->msg;

    if (!new)
        return;
    new->message = msg;
    new->next = NULL;
    if (!user->msg) {
        user->msg = new;
    } else {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    }
}

void load_message(int fd, struct load_data_s *load_data)
{
    struct save_message_s message = {0};

    if (read(fd, &message, sizeof(message)) != sizeof(message))
        return;
    if (!load_data->cur_user)
        return;
    add_msg_to_user(load_data->cur_user, message);
}

void add_user_to_list(struct save_user_s save_user, struct load_data_s *load)
{
    struct l_save_user_s *new = malloc(sizeof(struct l_save_user_s));
    struct l_save_user_s *current = load->user;

    new->user = save_user;
    new->next = NULL;
    new->joined = NULL;
    new->msg = NULL;
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

/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"

int get_max_fd_fct(data_server_t data)
{
    int m_fd = data.control_sckt;
    struct client_s *current = data.list_clients;

    while (current) {
        m_fd = (current->client_sckt > m_fd ? current->client_sckt : m_fd);
        current = current->next;
    }
    return (m_fd + 1);
}
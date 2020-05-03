/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int memory_running(int new_val)
{
    static int run = 0;

    if (new_val == 1)
        run = 1;
    else if (new_val == 42)
        return (run);
    return (0);
}

void sig_handler(int signal)
{
    if (signal == SIGINT)
        memory_running(1);
}

int setup_sigcatch(void)
{
    struct sigaction sig_act = {0};

    sig_act.sa_handler = sig_handler;
    return (sigaction(SIGINT, &sig_act, NULL));
}

bool server_running(void)
{
    if (memory_running(42) == 1) {
        puts("\rServeur will shutdown.");
        return (false);
    }
    return (true);
}
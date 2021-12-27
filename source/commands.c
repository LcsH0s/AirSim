#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "commands.h"

char *get_command()
{
    char *command = malloc(sizeof(char) * 100);
    scanf(" %s", command);
    return command;
}

int is_exit(const char *command)
{
    const char *cmd = "exit";
    if (strcmp(command, cmd) == 0)
        return 1;
    else
        return 0;
}

int is_time_warp(const char *command)
{
    const char *cmd = "timewarp";
    const char *cmd2 = "tw";
    if (strcmp(command, cmd) == 0)
        return 1;
    else if (strcmp(command, cmd2) == 0)
        return 1;
    else
        return 0;
}

int is_clear(const char *command)
{
    const char *cmd = "clear";
    if (strcmp(command, cmd) == 0)
        return 1;
    else
        return 0;
}

int is_add(const char *command)
{
    const char *cmd = "add";
    if (strcmp(command, cmd) == 0)
        return 1;
    else
        return 0;
}

int is_ls(const char *command)
{
    const char *cmd = "ls";
    if (strcmp(command, cmd) == 0)
        return 1;
    else
        return 0;
}

int is_land(const char *command)
{
    const char *cmd = "land";
    const char *cmd2 = "ld";
    if (strcmp(command, cmd) == 0)
        return 1;
    else if (strcmp(command, cmd2) == 0)
        return 1;
    else
        return 0;
}

int is_del(const char *command)
{
    const char *cmd = "del";
    if (strcmp(command, cmd) == 0)
        return 1;
    else
        return 0;
}

int is_info(const char *command)
{
    const char *cmd = "info";
    if (strcmp(command, cmd) == 0)
        return 1;
    else
        return 0;
}

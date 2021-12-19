#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "commands.h"

char *get_command()
{
    char *command = malloc(sizeof(char) * 100);
    scanf("%s", command);
    return command;
}

int is_exit(const char *command)
{
    const char *stop = "exit";
    if (strcmp(command, stop) == 0)
        return 1;
    else
        return 0;
}
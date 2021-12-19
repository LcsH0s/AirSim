#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "source/classes.h"
#include "source/commands.h"
#include "source/c_time.h"

int main(int argc, char *argv[])
{

    char *curr_cmd;
    char *curr_arg;

    c_time local_time = {0, 6, 1, 1, 2021};
    unsigned old_t = (unsigned)time(NULL);

    waiting_queue *takeoff_queue = (waiting_queue *)malloc(sizeof(waiting_queue));
    waiting_queue *landing_queue = (waiting_queue *)malloc(sizeof(waiting_queue));

    system("clear");

    while (1)
    {

        update_time(&local_time, old_t);
        old_t = (unsigned)time(NULL);
        disp_time(local_time);

        printf("[admin] ► ");
        curr_cmd = get_command();

        if (is_exit(curr_cmd))
            break;

        if (is_time_warp(curr_cmd))
        {
            curr_arg = get_command();
            increment_time(&local_time, atoi(curr_arg));
        }

        else if (is_clear(curr_cmd))
        {
            system("clear");
        }
    }

    printf("\x1b[34m[system] ► <Session Terminated>\x1b[0m\n");
    return 0;
}
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
    srand(time(NULL));
    char *curr_cmd;
    char *curr_arg;

    c_time local_time = {0, 6, 1, 1, 2021};
    unsigned old_t = (unsigned)time(NULL);

    waiting_queue *takeoff_queue = malloc(sizeof(waiting_queue));
    company **company_list = make_clist();

    wq_init(takeoff_queue);
    printf("\x1b[34m[system] ► Initialization sucessful!\x1b[0m\n");
    disp_wq(takeoff_queue);

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
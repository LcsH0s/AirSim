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
    waiting_queue *landing_queue = malloc(sizeof(waiting_queue));
    company **company_list = make_clist();

    printf("%s[system] ► Takeoff queue initializing", ANSI_COLOR_BLUE);
    fflush(stdout);
    delay(500);
    printf(".");
    fflush(stdout);
    delay(500);
    printf(".");
    fflush(stdout);
    delay(500);
    printf(".%s", ANSI_COLOR_RESET);
    fflush(stdout);
    delay(500);
    printf("\n");
    tk_init(takeoff_queue);
    disp_wq(takeoff_queue);

    printf("%s[system] ► Takeoff queue initializing", ANSI_COLOR_BLUE);
    fflush(stdout);
    delay(500);
    printf(".");
    fflush(stdout);
    delay(500);
    printf(".");
    fflush(stdout);
    delay(500);
    printf(".%s", ANSI_COLOR_RESET);
    fflush(stdout);
    delay(500);
    printf("\n");

    ld_init(landing_queue);
    disp_wq(landing_queue);
    printf("\n%s[system] ► Initialization Complete!%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);

    while (1)
    {
        update_time(&local_time, old_t);
        old_t = (unsigned)time(NULL);
        tk_update(takeoff_queue, local_time);
        disp_time(local_time);

        printf("[admin] ► ");
        curr_cmd = get_command();

        if (is_exit(curr_cmd))
        {
            printf("\x1b[34m[system] ► <Session Terminated>\x1b[0m\n");
            break;
        }
        if (is_time_warp(curr_cmd))
        {
            curr_arg = get_command();
            increment_time(&local_time, atoi(curr_arg));
        }

        else if (is_clear(curr_cmd))
        {
            system("clear");
        }

        else if (is_add(curr_cmd))
        {
            curr_arg = get_command();
            if ((strcmp(curr_arg, "-t") == 0) | (strcmp(curr_arg, "--takeoff") == 0))
                cmd_add(takeoff_queue);
            else if ((strcmp(curr_arg, "-l") == 0) | (strcmp(curr_arg, "--landing") == 0))
                cmd_add_rand_fuel(landing_queue);
        }

        else if (is_ls(curr_cmd))
        {
            curr_arg = get_command();
            if ((strcmp(curr_arg, "-t") == 0) | (strcmp(curr_arg, "--takeoff") == 0))
                disp_wq(takeoff_queue);
            else if ((strcmp(curr_arg, "-l") == 0) | (strcmp(curr_arg, "--landing") == 0))
                disp_wq(landing_queue);
        }

        else if (is_land(curr_cmd))
        {
            curr_arg = get_command();
            if ((strcmp(curr_arg, "-n") == 0) | (strcmp(curr_arg, "--number") == 0))
            {
                curr_arg = get_command();
                force_land(find_plane_by_number(landing_queue, atoi(curr_arg)));
            }
            if ((strcmp(curr_arg, "-i") == 0) | (strcmp(curr_arg, "--index") == 0))
            {
                curr_arg = get_command();
                force_land(find_plane_by_index(landing_queue, atoi(curr_arg) - 1));
            }
        }
        else if (is_del(curr_cmd))
        {
            curr_arg = get_command();
            if ((strcmp(curr_arg, "-t") == 0) | (strcmp(curr_arg, "--takeoff") == 0))
            {
                curr_arg = get_command();
                if ((strcmp(curr_arg, "-n") == 0) | (strcmp(curr_arg, "--number") == 0))
                {
                    curr_arg = get_command();
                    if (find_plane_by_number(takeoff_queue, atoi(curr_arg)))
                    {
                        printf("Plane N°%d sucessfully removed from takeoff queue\n", (find_plane_by_number(takeoff_queue, atoi(curr_arg)))->avion->number);
                        wq_del(find_plane_by_number(takeoff_queue, atoi(curr_arg)));
                    }
                    else
                        printf("Value Error: Please enter a valid plane number\n");
                }
                if ((strcmp(curr_arg, "-i") == 0) | (strcmp(curr_arg, "--index") == 0))
                {
                    curr_arg = get_command();
                    if (find_plane_by_index(takeoff_queue, atoi(curr_arg) - 1))
                    {
                        printf("Plane N°%d sucessfully removed from takeoff queue\n", (find_plane_by_index(takeoff_queue, atoi(curr_arg) - 1))->avion->number);
                        wq_del(find_plane_by_index(takeoff_queue, atoi(curr_arg) - 1));
                        printf("Successfully removed!\n");
                    }
                    else
                        printf("Index Error : Please enter a valid index\n");
                }
            }
            else if ((strcmp(curr_arg, "-l") == 0) | (strcmp(curr_arg, "--landing") == 0))
            {
                curr_arg = get_command();
                if ((strcmp(curr_arg, "-n") == 0) | (strcmp(curr_arg, "--number") == 0))
                {
                    curr_arg = get_command();
                    if (find_plane_by_number(landing_queue, atoi(curr_arg)))
                    {
                        printf("Plane N°%d sucessfully removed from landing queue\n", (find_plane_by_number(landing_queue, atoi(curr_arg)))->avion->number);
                        wq_del(find_plane_by_number(landing_queue, atoi(curr_arg)));
                    }
                    else
                        printf("Value Error: Please enter a valid plane number\n");
                }
                if ((strcmp(curr_arg, "-i") == 0) | (strcmp(curr_arg, "--index") == 0))
                {
                    curr_arg = get_command();
                    if (find_plane_by_index(landing_queue, atoi(curr_arg) - 1))
                    {
                        printf("Plane N°%d sucessfully removed from landing queue\n", (find_plane_by_index(landing_queue, atoi(curr_arg) - 1))->avion->number);
                        wq_del(find_plane_by_index(landing_queue, atoi(curr_arg) - 1));
                    }
                    else
                        printf("Index Error : Please enter a valid index\n");
                }
            }
        }
        else if (is_info(curr_cmd))
        {
            curr_arg = get_command();
            if ((strcmp(curr_arg, "-t") == 0) | (strcmp(curr_arg, "--takeoff") == 0))
            {
                curr_arg = get_command();
                if ((strcmp(curr_arg, "-n") == 0) | (strcmp(curr_arg, "--number") == 0))
                {
                    curr_arg = get_command();
                    if (find_plane_by_number(takeoff_queue, atoi(curr_arg)))
                    {
                        p_info(find_plane_by_number(takeoff_queue, atoi(curr_arg)));
                    }
                    else
                        printf("Value Error: Please enter a valid plane number\n");
                }
                if ((strcmp(curr_arg, "-i") == 0) | (strcmp(curr_arg, "--index") == 0))
                {
                    curr_arg = get_command();
                    if (find_plane_by_index(takeoff_queue, atoi(curr_arg) - 1))
                    {
                        p_info(find_plane_by_index(takeoff_queue, atoi(curr_arg) - 1));
                    }
                    else
                        printf("Index Error : Please enter a valid index\n");
                }
            }
            else if ((strcmp(curr_arg, "-l") == 0) | (strcmp(curr_arg, "--landing") == 0))
            {
                curr_arg = get_command();
                if ((strcmp(curr_arg, "-n") == 0) | (strcmp(curr_arg, "--number") == 0))
                {
                    curr_arg = get_command();
                    if (find_plane_by_number(landing_queue, atoi(curr_arg)))
                    {
                        p_info(find_plane_by_number(landing_queue, atoi(curr_arg)));
                    }
                    else
                        printf("Value Error: Please enter a valid plane number\n");
                }
                if ((strcmp(curr_arg, "-i") == 0) | (strcmp(curr_arg, "--index") == 0))
                {
                    curr_arg = get_command();
                    if (find_plane_by_index(landing_queue, atoi(curr_arg) - 1))
                    {
                        p_info(find_plane_by_index(landing_queue, atoi(curr_arg) - 1));
                    }
                    else
                        printf("Index Error : Please enter a valid index\n");
                }
            }
            else if ((strcmp(curr_arg, "-a") == 0) | (strcmp(curr_arg, "--all") == 0))
            {
                printf("%s[info] ► Takeoff queue: \n", ANSI_COLOR_MAGENTA);
                info_all(takeoff_queue);
                printf("%s[info] ► Landing queue:\n", ANSI_COLOR_MAGENTA);
                info_all(landing_queue);
            }
        }
    }

    return 0;
}
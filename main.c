#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "source/classes.h"
#include "source/commands.h"
#include "source/c_time.h"

#define LOG_FILE_NAME "log/aeroport_log.txt"

int main(int argc, char *argv[])
{

    srand(time(NULL));
    char *curr_cmd;
    char *curr_arg;
    log_file = fopen("log/aeroport_log.txt", "a+");
    if (log_file == NULL)
    {
        printf("%s[error] ► Impossible to open log file.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
        fprintf(log_file, "%s[error] ► Impossible to open log file.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
        printf("\x1b[34m[system] ► <Session Terminated>\x1b[0m\n");
        fprintf(log_file, "\x1b[34m[system] ► <Session Terminated>\x1b[0m\n");
        return 0;
    }

    c_time local_time = {0, 6, 1, 1, 2021};
    unsigned old_t = (unsigned)time(NULL);

    waiting_queue *takeoff_queue = malloc(sizeof(waiting_queue));
    waiting_queue *landing_queue = malloc(sizeof(waiting_queue));
    company **company_list = make_clist(), **black_list = make_bl();


    printf("%s[system] ► Takeoff queue initializing...%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    fprintf(log_file, "%s[system] ► Takeoff queue initializing...%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);

    tk_init(takeoff_queue);
    disp_wq(takeoff_queue);

    printf("%s[system] ► Takeoff queue initializing...%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    fprintf(log_file, "%s[system] ► Takeoff queue initializing...%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);

    ld_init(landing_queue);
    disp_wq(landing_queue);
    printf("\n%s[system] ► Initialization Complete!%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
    fprintf(log_file, "\n%s[system] ► Initialization Complete!%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);

    while (1)
    {
        update_time(&local_time, old_t);
        old_t = (unsigned)time(NULL);
        tk_update(takeoff_queue, local_time, black_list);
        ld_update(landing_queue, local_time, black_list);
        disp_time(local_time);

        printf("[admin] ► ");
        curr_cmd = get_command();
        fprintf(log_file, "[admin] ► %s\n", curr_cmd);
        if (is_exit(curr_cmd))
        {
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
            else if ((strcmp(curr_arg, "-b") == 0) | (strcmp(curr_arg, "--blacklist") == 0))
                disp_bl(black_list);
            else if ((strcmp(curr_arg, "-c") == 0) | (strcmp(curr_arg, "--companies") == 0))
                disp_clist(company_list);
            else if ((strcmp(curr_arg, "-cc") == 0) | (strcmp(curr_arg, "--comp-caracteristics") == 0))
            {
                curr_arg = get_command();
                disp_cc(get_company_by_acronym(curr_arg), takeoff_queue, landing_queue);
            }
        }
        else if (is_land(curr_cmd))
        {
            curr_arg = get_command();
            if ((strcmp(curr_arg, "-n") == 0) | (strcmp(curr_arg, "--number") == 0))
            {
                curr_arg = get_command();
                land(find_plane_by_number(landing_queue, atoi(curr_arg)));
            }
            else if ((strcmp(curr_arg, "-i") == 0) | (strcmp(curr_arg, "--index") == 0))
            {
                curr_arg = get_command();
                land(find_plane_by_index(landing_queue, atoi(curr_arg) - 1));
            }
            else if ((strcmp(curr_arg, "-!") == 0) | (strcmp(curr_arg, "--emergency") == 0))
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
                        printf("%s[info] ► Plane N°%d sucessfully removed from takeoff queue%s\n", ANSI_COLOR_GREEN, (find_plane_by_number(takeoff_queue, atoi(curr_arg)))->avion->number, ANSI_COLOR_RESET);
                        fprintf(log_file, "%s[info] ► Plane N°%d sucessfully removed from takeoff queue%s\n", ANSI_COLOR_GREEN, (find_plane_by_number(takeoff_queue, atoi(curr_arg)))->avion->number, ANSI_COLOR_RESET);
                        wq_del(find_plane_by_number(takeoff_queue, atoi(curr_arg)));
                    }
                    else
                    {
                        printf("%s[error] ► Value Error: Please enter a valid plane number%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                        fprintf(log_file, "%s[error] ► Value Error: Please enter a valid plane number%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                    }
                }
                if ((strcmp(curr_arg, "-i") == 0) | (strcmp(curr_arg, "--index") == 0))
                {
                    curr_arg = get_command();
                    if (find_plane_by_index(takeoff_queue, atoi(curr_arg) - 1))
                    {
                        printf("%s[info] ► Plane N°%d sucessfully removed from takeoff queue%s\n", ANSI_COLOR_GREEN, (find_plane_by_index(takeoff_queue, atoi(curr_arg) - 1))->avion->number, ANSI_COLOR_RESET);
                        fprintf(log_file, "%s[info] ► Plane N°%d sucessfully removed from takeoff queue%s\n", ANSI_COLOR_GREEN, (find_plane_by_index(takeoff_queue, atoi(curr_arg) - 1))->avion->number, ANSI_COLOR_RESET);
                        wq_del(find_plane_by_index(takeoff_queue, atoi(curr_arg) - 1));
                    }
                    else
                    {
                        printf("%s[error] ► Index Error : Please enter a valid index%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                        fprintf(log_file, "%s[error] ► Index Error : Please enter a valid index%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                    }
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
                        printf("%s[info] ► Plane N°%d sucessfully removed from landing queue%s\n", ANSI_COLOR_GREEN, (find_plane_by_number(landing_queue, atoi(curr_arg)))->avion->number, ANSI_COLOR_RESET);
                        fprintf(log_file, "%s[info] ► Plane N°%d sucessfully removed from landing queue%s\n", ANSI_COLOR_GREEN, (find_plane_by_number(landing_queue, atoi(curr_arg)))->avion->number, ANSI_COLOR_RESET);
                        wq_del(find_plane_by_number(landing_queue, atoi(curr_arg)));
                    }
                    else
                    {
                        printf("%s[error] ► Value Error: Please enter a valid plane number%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                        fprintf(log_file, "%s[error] ► Value Error: Please enter a valid plane number%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                    }
                }
                if ((strcmp(curr_arg, "-i") == 0) | (strcmp(curr_arg, "--index") == 0))
                {
                    curr_arg = get_command();
                    if (find_plane_by_index(landing_queue, atoi(curr_arg) - 1))
                    {
                        printf("%s[info] ► Plane N°%d sucessfully removed from landing queue%s\n", ANSI_COLOR_GREEN, (find_plane_by_index(landing_queue, atoi(curr_arg) - 1))->avion->number, ANSI_COLOR_RESET);
                        fprintf(log_file, "%s[info] ► Plane N°%d sucessfully removed from landing queue%s\n", ANSI_COLOR_GREEN, (find_plane_by_index(landing_queue, atoi(curr_arg) - 1))->avion->number, ANSI_COLOR_RESET);
                        wq_del(find_plane_by_index(landing_queue, atoi(curr_arg) - 1));
                    }
                    else
                    {
                        printf("%s[error] ► Index Error : Please enter a valid index%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                        fprintf(log_file, "%s[error] ► Index Error : Please enter a valid index%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                    }
                }
            }
        }
        else if (is_info(curr_cmd))
        {
            curr_arg = get_command();
            if ((strcmp(curr_arg, "-t") == 0) | (strcmp(curr_arg, "--takeoff") == 0))
            {
                printf("%s[info] ► Takeoff queue: \n", ANSI_COLOR_MAGENTA);
                fprintf(log_file, "%s[info] ► Takeoff queue: \n", ANSI_COLOR_MAGENTA);
                info_all(takeoff_queue);
            }

            else if ((strcmp(curr_arg, "-l") == 0) | (strcmp(curr_arg, "--landing") == 0))
            {
                printf("%s[info] ► Landing queue:\n", ANSI_COLOR_MAGENTA);
                fprintf(log_file, "%s[info] ► Landing queue:\n", ANSI_COLOR_MAGENTA);
                info_all(landing_queue);
            }
            else if ((strcmp(curr_arg, "-a") == 0) | (strcmp(curr_arg, "--all") == 0))
            {
                printf("%s[info] ► Takeoff queue: \n", ANSI_COLOR_MAGENTA);
                fprintf(log_file, "%s[info] ► Takeoff queue: \n", ANSI_COLOR_MAGENTA);
                info_all(takeoff_queue);
                printf("%s[info] ► Landing queue:\n", ANSI_COLOR_MAGENTA);
                fprintf(log_file, "%s[info] ► Landing queue:\n", ANSI_COLOR_MAGENTA);
                info_all(landing_queue);
            }
        }
        else if (is_man(curr_cmd))
        {
            FILE *fptr;
            fptr = fopen("conf/manual.man", "r");
            if (fptr == NULL)
            {
                printf("%s[error] ► Cannot open file %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                fprintf(log_file, "%s[error] ► Cannot open file %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                exit(0);
            }

            // Read contents from file
            printf("%s", ANSI_COLOR_MAGENTA);
            fprintf(log_file, "%s", ANSI_COLOR_MAGENTA);
            char c = fgetc(fptr);
            while (c != EOF)
            {
                printf("%c", c);
                fprintf(log_file, "%c", c);
                c = fgetc(fptr);
            }

            fclose(fptr);
            printf("\n%s", ANSI_COLOR_RESET);
            fprintf(log_file, "\n%s", ANSI_COLOR_RESET);
        }
        else if (is_bl(curr_cmd))
        {
            curr_arg = get_command();
            if ((strcmp(curr_arg, "-a") == 0) | (strcmp(curr_arg, "add") == 0))
            {
                curr_arg = get_command();
                blacklist_add(black_list, get_company_by_acronym(curr_arg));
            }
            if ((strcmp(curr_arg, "-r") == 0) | (strcmp(curr_arg, "remove") == 0))
            {
                curr_arg = get_command();
                blacklist_remove(black_list, get_company_by_acronym(curr_arg));
            }
        }
        else
        {
            printf("%s[error] ► Unknown command. To see available commands, open manual with command 'man'%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
            fprintf(log_file, "%s[error] ► Unknown command. To see available commands, open manual with command 'man'%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
        }
    }

    fclose(log_file);
    printf("\x1b[34m[system] ► <Session Terminated>\x1b[0m\n");
    fprintf(log_file, "\x1b[34m[system] ► <Session Terminated>\x1b[0m\n");

    return 0;
}

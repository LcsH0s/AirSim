#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "source/avion.h"
#include "source/commands.h"
#include "source/c_time.h"

int main(int argc, char *argv[])
{

    char *current_command;
    struct t_time l_time = {0, 6, 1, 1, 2021};
    unsigned old_t = (unsigned)time(NULL);

    while (1)
    {
        update_time(&l_time, old_t);
        old_t = (unsigned)time(NULL);
        disp_time(l_time);

        current_command = get_command();
        if (is_exit(current_command))
            break;
    }

    printf("<Session Terminated>\n");
    return 0;
}
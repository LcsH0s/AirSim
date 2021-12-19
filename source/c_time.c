#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_time.h"

void update_time(struct c_time *l_time, unsigned old_t)
{
    unsigned new_t = (unsigned)time(NULL);
    unsigned delta = new_t - old_t;

    for (int i = 0; i < delta; i++)
    {
        l_time->min += 1;
        if (l_time->min == 60)
        {
            l_time->hour += 1;
            l_time->min = 0;
        }
        if (l_time->hour == 24)
        {
            l_time->day += 1;
            l_time->hour = 0;
        }
        if (l_time->day == 31)
        {
            l_time->day = 1;
            l_time->month += 1;
        }
        if (l_time->month == 13)
        {
            l_time->month = 1;
            l_time->year += 1;
        }
    }
}

void disp_time(struct c_time time)
{

    if (time.day > 9)
        printf("Time is : [%d", time.day);
    else
        printf("Time is : [0%d", time.day);

    if (time.month < 10)
        printf("/0%d", time.month);
    else
        printf("/%d", time.month);

    printf("/%d", time.year);

    if (time.hour > 9)
        printf(" %d", time.hour);
    else
        printf(" 0%d", time.hour);

    if (time.min > 9)
        printf(":%d", time.min);
    else
        printf(":0%d", time.min);

    printf(":%d]\n", (10 + rand() % 50));
}

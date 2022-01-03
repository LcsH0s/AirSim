#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_time.h"

extern FILE *log_file;

void update_time(c_time *l_time, unsigned old_t)
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
void increment_time(c_time *l_time, unsigned add)
{

    for (int i = 0; i < add; i++)
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

void disp_time(c_time time)
{

    if (time.day > 9)
    {
        printf("%s[system] ► Time is : [%d", "\x1b[34m", time.day);
        fprintf(log_file, "%s[system] ► Time is : [%d", "\x1b[34m", time.day);
    }
    else
    {
        printf("%s[system] ► Time is : [0%d", "\x1b[34m", time.day);
        fprintf(log_file, "%s[system] ► Time is : [0%d", "\x1b[34m", time.day);
    }

    if (time.month < 10)
    {
        printf("/0%d", time.month);
        fprintf(log_file, "/0%d", time.month);
    }
    else
    {
        printf("/%d", time.month);
        fprintf(log_file, "/%d", time.month);
    }

    printf("/%d", time.year);
    fprintf(log_file, "/%d", time.year);

    if (time.hour > 9)
    {
        printf(" %d", time.hour);
        fprintf(log_file, " %d", time.hour);
    }
    else
    {
        printf(" 0%d", time.hour);
        fprintf(log_file, " 0%d", time.hour);
    }

    if (time.min > 9)
    {
        printf(":%d", time.min);
        fprintf(log_file, ":%d", time.min);
    }
    else
    {
        printf(":0%d", time.min);
        fprintf(log_file, ":0%d", time.min);
    }

    printf(":%d]%s\n", (10 + rand() % 50), "\x1b[0m");
    fprintf(log_file, ":%d]%s\n", (10 + rand() % 50), "\x1b[0m");
}

void str_time(c_time time)
{
    if (time.hour > 9)
    {
        printf(" %d", time.hour);
        fprintf(log_file, " %d", time.hour);
    }
    else
    {
        printf(" 0%d", time.hour);
        fprintf(log_file, " 0%d", time.hour);
    }
    if (time.min > 9)
    {
        printf(":%d", time.min);
        fprintf(log_file, ":%d", time.min);
    }
    else
    {
        printf(":0%d", time.min);
        fprintf(log_file, ":0%d", time.min);
    }
    printf(":00");
    fprintf(log_file, ":00");
}

void delay(unsigned int msecs)
{
    clock_t goal = msecs * CLOCKS_PER_SEC / 1000 + clock(); // convert msecs to clock count
    while (goal > clock())
        ;
}

int time_cmp(c_time a, c_time b)
{
    if (a.year > b.year)
    {
        return 1;
    }
    else if (a.year < b.year)
    {
        return 0;
    }
    else
    {
        if (a.month > b.month)
        {
            return 1;
        }
        else if (a.month < b.month)
        {
            return 0;
        }
        else
        {
            if (a.day > b.day)
            {
                return 1;
            }
            else if (a.day < b.day)
            {
                return 0;
            }
            else
            {
                if (a.hour > b.hour)
                {
                    return 1;
                }
                else if (a.hour < b.hour)
                {
                    return 0;
                }
                else
                {
                    if (a.min >= b.min)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
    }
}

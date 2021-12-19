#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "classes.h"
#include "c_time.h"

plane *p_init(int fuel_level, char number[8], char company[3], c_time arrival)
{
    plane *tmp = (plane *)malloc(sizeof(plane));
    *tmp = (plane){.fuel = fuel_level, .number = number, .company = company, .arrival = arrival};
    return tmp;
}

company *c_init(char *name, char acronym[3])
{
    company *tmp = (company *)malloc(sizeof(company));
    *tmp = (company){.name = name, .acronym = acronym, .plane_list = malloc(sizeof(plane) * 1000)};
    return tmp;
}

void wq_add(waiting_queue *wq, plane p)
{
}

event_queue *eq_add()
{
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "classes.h"
#include "c_time.h"

plane *p_init(float fuel_level, unsigned number, company *comp, c_time *arrival)
{
    plane *p = malloc(sizeof(plane *));
    *p = (plane){.fuel = fuel_level, .number = number, .comp = comp, .arrival = arrival};
    return p;
}

company *c_init(char *name, char *acronym)
{
    company *c = malloc(sizeof(company));
    *c = (company){.name = strdup(name), .acronym = strdup(acronym)};
    return c;
}

company **make_clist()
{
    company **company_list = malloc(sizeof(company *) * 4);
    company_list[0] = c_init(("Luftansa"), "LUF");
    company_list[1] = c_init("AirFrance", "AFR");
    company_list[2] = c_init("Transavia", "TRA");
    company_list[3] = c_init("EasyJet", "EJT");
    return company_list;
}

void wq_add(waiting_queue *wq, plane *p)
{
    waiting_queue *current = wq;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(waiting_queue));
    current->next->avion = p;
    current->next->next = NULL;
}

void disp_wq(waiting_queue *wq)
{
    printf("Flight Number  : %u\n", wq->avion->number);
    if (wq->next != NULL)
    {
        disp_wq(wq->next);
    }
}

company *get_company_by_acronym(char *acronym)
{
    company **clist = make_clist();
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(clist[i]->acronym, acronym) == 0)
            return clist[i];
    }
    return clist[0];
}

void wq_init(waiting_queue *wq)
{
    FILE *f = fopen("events/init_planes.event", "r");
    unsigned fsize, number;
    float fuel;
    char acronym[10];
    int min, hour, day, month, year;

    if (f == NULL)
    {
        printf("\x1B[31m[ERROR] ► File Error: Program could not initialize due to missing 'init_planes.event' file\033[0m\n");
        exit(-1); // must include stdlib.h
    }
    fscanf(f, "%u", &fsize);

    fscanf(f, "%f %u %s %d %d %d %d %d", &fuel, &number, acronym, &min, &hour, &day, &month, &year);
    wq->avion = p_init(fuel, number, get_company_by_acronym(acronym), &(c_time){.min = min, .day = day, .hour = hour, .month = month, .year = year});
    wq->next = NULL;

    for (int i = 1; i < fsize; i++)
    {
        fscanf(f, "%f %u %s %d %d %d %d %d", &fuel, &number, acronym, &min, &hour, &day, &month, &year);
        wq_add(wq, p_init(fuel, number, get_company_by_acronym(acronym), &(c_time){.min = min, .day = day, .hour = hour, .month = month, .year = year}));
    }
}
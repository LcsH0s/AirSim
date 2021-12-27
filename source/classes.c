#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "classes.h"
#include "c_time.h"

plane *p_init(float fuel_level, unsigned number, company *comp, c_time *arrival)
{
    plane *p = malloc(sizeof(plane *));
    *p = (plane){.fuel = fuel_level, .number = number, .comp = comp, .arrival = malloc(sizeof(c_time))};
    p->arrival->min = arrival->min;
    p->arrival->hour = arrival->hour;
    p->arrival->day = arrival->day;
    p->arrival->month = arrival->month;
    p->arrival->year = arrival->year;
    return p;
}

company *c_init(char *name, char *acronym)
{
    company *c = malloc(sizeof(company));
    *c = (company){.name = strdup(name), .acronym = strdup(acronym)};
    return c;
}

waiting_queue *seek_head(waiting_queue *wq)
{
    while (wq->prev != NULL)
        wq = wq->prev;
    return wq;
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

void p_info(waiting_queue *wq)
{
    printf("%s[info] ► Information on plane N°%d : %s", ANSI_COLOR_CYAN, wq->avion->number, ANSI_COLOR_RESET);
    printf("%sFuel Level : %.1f Company : %s Arrival : %s", ANSI_COLOR_CYAN, wq->avion->fuel, wq->avion->comp->acronym, ANSI_COLOR_RESET);
    str_time(*(wq->avion->arrival));
    printf("\n");
}

void info_all(waiting_queue *wq)
{
    if (wq->avion == NULL)
    {
        printf("%sN/A %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
        return;
    }
    wq = seek_head(wq);
    while (wq->next != NULL)
    {
        p_info(wq);
        wq = wq->next;
    }
    p_info(wq);
}

void wq_add(waiting_queue *wq, plane *p)
{
    waiting_queue *current = seek_head(wq);
    wq = seek_head(wq);
    if (wq->avion == NULL)
    {
        wq->avion = p;
        return;
    }

    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(waiting_queue));
    current->next->avion = p;
    current->next->next = NULL;
    current->next->prev = current;
}

void disp_wq(waiting_queue *wq)
{
    wq = seek_head(wq);
    if (wq->avion == NULL)
    {
        printf("%s[info] ► N/A%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
        return;
    }
    while (wq->next != NULL)
    {
        printf("%s[info] ► Flight number : %d%s\n", ANSI_COLOR_CYAN, wq->avion->number, ANSI_COLOR_RESET);
        wq = wq->next;
    }
    printf("%s[info] ► Flight number : %d%s\n", ANSI_COLOR_CYAN, wq->avion->number, ANSI_COLOR_RESET);
}

void tk_init(waiting_queue *wq)
{
    FILE *f = fopen("events/init_planes_tk.event", "r");
    unsigned fsize, number;
    float fuel;
    char acronym[10];
    int min, hour, day, month, year;

    if (f == NULL)
    {
        printf("\x1B[31m[ERROR] ► File Error: Program could not initialize due to missing 'init_planes_tk.event' file\033[0m\n");
        exit(-1); // must include stdlib.h
    }

    fscanf(f, "%u", &fsize);
    fscanf(f, "%f %u %s %d %d %d %d %d", &fuel, &number, acronym, &min, &hour, &day, &month, &year);
    wq->avion = p_init(fuel, number, get_company_by_acronym(acronym), &(c_time){.min = min % 60, .day = day % 31, .hour = hour % 24, .month = month % 12, .year = year});
    wq->next = NULL;
    wq->prev = NULL;

    for (int i = 1; i < fsize; i++)
    {
        fscanf(f, "%f %u %s %d %d %d %d %d", &fuel, &number, acronym, &min, &hour, &day, &month, &year);
        wq_add(wq, p_init(fuel, number, get_company_by_acronym(acronym), &(c_time){.min = min % 60, .day = day % 31, .hour = hour % 24, .month = month % 12, .year = year}));
    }
}

void ld_init(waiting_queue *wq)
{
    FILE *f = fopen("events/init_planes_ld.event", "r");
    unsigned fsize, number;
    float fuel;
    char acronym[10];
    int min, hour, day, month, year;

    if (f == NULL)
    {
        printf("\x1B[31m[ERROR] ► File Error: Program could not initialize due to missing 'init_planes_ld.event' file\033[0m\n");
        exit(-1); // must include stdlib.h
    }

    fscanf(f, "%u", &fsize);
    fscanf(f, "%f %u %s %d %d %d %d %d", &fuel, &number, acronym, &min, &hour, &day, &month, &year);
    wq->avion = p_init(fuel, number, get_company_by_acronym(acronym), &(c_time){.min = min % 60, .day = day % 31, .hour = hour % 24, .month = month % 12, .year = year});
    wq->next = NULL;
    wq->prev = NULL;
    for (int i = 1; i < fsize; i++)
    {
        fscanf(f, "%f %u %s %d %d %d %d %d", &fuel, &number, acronym, &min, &hour, &day, &month, &year);
        wq_add(wq, p_init(fuel, number, get_company_by_acronym(acronym), &(c_time){.min = min % 60, .day = day % 31, .hour = hour % 24, .month = month % 12, .year = year}));
    }
}

void cmd_add(waiting_queue *wq)
{
    unsigned number;
    float fuel;
    char acronym[10];
    int min, hour, day, month, year;

    printf("Flight number : ");
    scanf(" %u", &number);
    printf("Fuel level (percentage) : ");
    scanf(" %f", &fuel);
    printf("Acronym : ");
    fflush(stdin);
    scanf("%s", acronym);
    printf("Arrival Time :\nMinute : ");
    scanf(" %d", &min);
    printf("Hour : ");
    scanf(" %d", &hour);
    printf("Day : ");
    scanf(" %d", &day);
    printf("Month : ");
    scanf(" %d", &month);
    printf("Year : ");
    scanf(" %d", &year);

    wq_add(wq, p_init(fuel, number, get_company_by_acronym(acronym), &(c_time){.min = min % 60, .day = day % 31, .hour = hour % 24, .month = month % 12, .year = year}));
}

void cmd_add_rand_fuel(waiting_queue *wq)
{
    unsigned number;
    char acronym[10];
    int min, hour, day, month, year;

    printf("Flight number : ");
    scanf(" %u", &number);
    printf("Acronym : ");
    fflush(stdin);
    scanf("%s", acronym);
    printf("Arrival Time :\nMinute : ");
    scanf(" %d", &min);
    printf("Hour : ");
    scanf(" %d", &hour);
    printf("Day : ");
    scanf(" %d", &day);
    printf("Month : ");
    scanf(" %d", &month);
    printf("Year : ");
    scanf(" %d", &year);

    wq_add(wq, p_init(10 + rand() % 90, number, get_company_by_acronym(acronym), &(c_time){.min = min % 60, .day = day % 31, .hour = hour % 24, .month = month % 12, .year = year}));
}

waiting_queue *find_plane_by_number(waiting_queue *wq, unsigned number)
{
    while (wq->next != NULL)
    {
        if (wq->avion->number == number)
            return wq;
        wq = wq->next;
    }
    if (wq->avion->number == number)
        return wq;
    return NULL;
}

waiting_queue *find_plane_by_index(waiting_queue *wq, unsigned index)
{
    for (int i = 0; i < index; i++)
    {
        if (wq->next == NULL)
        {
            printf("%s[error] ► Index Error: Index exceeds waiting queue size%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
            return NULL;
        }
        wq = wq->next;
    }
    return wq;
}

void wq_del(waiting_queue *wq)
{
    waiting_queue *current = wq;
    if ((current->prev == NULL) & (current->next == NULL))
    {
        wq->avion = NULL;
        return;
    }

    else if (current->prev == NULL)
    {
        waiting_queue *to_pop = wq->next;
        wq->avion = wq->next->avion;
        to_pop->avion = NULL;
        wq->next = wq->next->next;
        if ((wq->next != NULL))
            wq->next->prev = wq;
        free(to_pop);
    }

    else if (current->next == NULL)
    {
        current->prev->next = NULL;
        free(current);
    }

    else
    {
        current->next->prev = current->prev;
        current->prev->next = current->next;
        free(current);
    }
}

void force_land(waiting_queue *wq)
{
    printf("%s[system] ► Due to an emergency, the plane N°%d has now priority to land\n All other planes will be consequently delayed.%s\n", ANSI_COLOR_YELLOW, wq->avion->number, ANSI_COLOR_RESET);
    printf("%s[system] ► Plane N°%d has securly taken off\n Emergency state lifted%s\n", ANSI_COLOR_GREEN, wq->avion->number, ANSI_COLOR_RESET);
    wq_del(wq);
}

void tk_update(waiting_queue *wq, c_time local_time)
{
    wq = seek_head(wq);
    if (wq->avion == NULL)
        return;
    if (time_cmp(local_time, *(wq->avion->arrival)))
    {
        printf("%s[info] ► Plane number N°%d has landed at ", ANSI_COLOR_CYAN, wq->avion->number);
        str_time(*(wq->avion->arrival));
        printf("%s\n", ANSI_COLOR_RESET);

        wq_del(wq);
        tk_update(wq, local_time);
        if (wq->avion == NULL)
            return;
    }
}
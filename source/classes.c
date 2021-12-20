#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "classes.h"
#include "c_time.h"

plane *p_init(unsigned fuel_level, unsigned number, company *company, c_time *arrival)
{

    return (&(plane){.fuel = fuel_level, .number = number, .comp = company, .arrival = arrival});
}

company *c_init(char *name, char *acronym)
{
    return (&(company){.name = (char *[]){name}, .acronym = (char *[]){acronym}});
}

company **make_clist()
{
    company **company_list = malloc(sizeof(company *) * 4);
    company_list[0] = c_init("Luftansa", "LUF");
    company_list[1] = c_init("AirFrance", "AFR");
    company_list[2] = c_init("Transavia", "TRA");
    company_list[3] = c_init("EasyJet", "EJT");
    return company_list;
}

void wq_add(waiting_queue *wq, plane *p)
{
    if (wq->avion)
        wq->next = &(waiting_queue){.avion = p, .next = NULL};
    else
    {
        wq->avion = p;
        wq->next = NULL;
    }
}

void disp_wq(waiting_queue *wq)
{
    if (wq->avion)
    {
        printf("Plane in wainting queue are :\n");
        /*
                waiting_queue *dwq = wq;
                for (dwq = wq; dwq->next != NULL; dwq = dwq->next)
                {
                    printf("Plane fuel : %d\nPlane Number : %u\nPlane Company : \n", dwq->avion->fuel, dwq->avion->number);
                }*/
        company *c = wq->avion->comp;
        printf("Plane fuel : %u\nPlane Number : %u\nPlane Company : %s\n", (wq->avion->fuel), wq->avion->number, *(c->name));
    }
}

void eq_add()
{
}

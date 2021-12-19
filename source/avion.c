#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avion.h"

tarmac *init()
{
    tarmac *temp;
    temp = (tarmac *)malloc(sizeof(tarmac));
    temp->fuel = 0;
    temp->next = NULL;
}

tarmac *addqueue(tarmac *head, float fuel_level, char company_name[10], char plane_model[10])
{
    tarmac *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = (tarmac *)malloc(sizeof(tarmac));
    temp->next->fuel = fuel_level;
    strcpy(temp->next->model, plane_model);
    strcpy(temp->next->company, company_name);
    return head;
}

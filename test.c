#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct avion
{
    float fuel;
    char model[10];
    char company[10];
} plane;

typedef struct queue
{
    plane avion;
    struct queue *next;
} waiting_queue;

typedef struct companie
{
    plane avion;
    char name[10];
    char acronyme[3];
    struct companie *next;
};

waiting_queue *init()
{
    waiting_queue *temp;
    temp = (waiting_queue *)malloc(sizeof(waiting_queue));
    temp->next = NULL;
}

waiting_queue *addqueue_choosefuel(waiting_queue *head, float essence, char)
{
    waiting_queue *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = (waiting_queue *)malloc(sizeof(waiting_queue));
    temp->avion.fuel = essence;
    strcpy(temp->next->model, plane_model);
    strcpy(temp->next->company, company_name);
    return head;
}

void parcourir(tarmac *head)
{
    tarmac *temp = head;
    if (temp != NULL)
    {
        printf("name : %s fuel : %f\n", temp->model, temp->fuel);
        temp = temp->next;
        parcourir(temp);
    }
}

int main()
{
    tarmac *piste;
    tarmac *listep;
    listep = init();
    piste = listep;
    float fue = 5;
    char marque[10];
    char nom[10];
    printf("nom de l'avion :\n");
    scanf("%s", nom);
    printf("marque de l'avion :\n");
    scanf("%s", marque);
    addqueue(piste, fue, marque, nom);
    parcourir(piste);
    return 0;
}
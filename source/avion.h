#ifndef AVION_H_ /* Include guard */
#define AVION_H_

typedef struct
{
    float fuel;
    char number[8];
    char company[3];
} plane;

typedef struct
{
    plane avion;
    struct waiting_queue *next;
} waiting_queue;

typedef struct
{
    plane avion;
    char name[10];
    char acronym[3];
    struct company *next;
} company;

#endif
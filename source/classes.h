#ifndef CLASSES_H_ /* Include guard */
#define CLASSES_H_

#include "c_time.h"

typedef struct
{
    int fuel;
    char number[8];
    char company[3];
    c_time arrival;
} plane;

typedef struct
{
    plane *avion;
    struct waiting_queue *next;
} waiting_queue;

typedef struct
{
    char event[3];
    struct event_queue *next;
} event_queue;

typedef struct
{
    char *name;
    char acronym[3];
    plane *plane_list;
} company;

#endif
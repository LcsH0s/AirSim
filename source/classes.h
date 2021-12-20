#ifndef CLASSES_H_ /* Include guard */
#define CLASSES_H_

#include "c_time.h"

typedef struct company company;
typedef struct plane plane;
typedef struct waiting_queue waiting_queue;
typedef struct event_queue event_queue;

struct company
{
    char *name;
    char *acronym;
};

struct plane
{
    float fuel;
    unsigned number;
    company *comp;
    c_time *arrival;
};

struct waiting_queue
{
    plane *avion;
    waiting_queue *next;
};

struct event_queue
{
    char *event;
    event_queue *next;
};

plane *p_init(float fuel_level, unsigned number, company *company, c_time *arrival);
company *c_init(char *name, char *acronym);
company **make_clist();
void wq_add(waiting_queue *wq, plane *p);
void disp_wq(waiting_queue *wq);
void wq_init(waiting_queue *wq);

#endif
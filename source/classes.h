#ifndef CLASSES_H_ /* Include guard */
#define CLASSES_H_

#include "c_time.h"

typedef struct company company;
typedef struct plane plane;
typedef struct waiting_queue waiting_queue;
typedef struct event_queue event_queue;
typedef struct black_list black_list;

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
    waiting_queue *prev;
};

struct event_queue
{
    char *event;
    event_queue *next;
};

struct black_list
{
    char *acronym;
    black_list *next;
};

plane *
p_init(float fuel_level, unsigned number, company *company, c_time *arrival);
company *c_init(char *name, char *acronym);
company **make_clist();
void wq_add(waiting_queue *wq, plane *p);
void disp_wq(waiting_queue *wq);
void tk_init(waiting_queue *wq);
void ld_init(waiting_queue *wq);
void cmd_add(waiting_queue *wq);
void cmd_add_rand_fuel(waiting_queue *wq);
waiting_queue *find_plane_by_number(waiting_queue *wq, unsigned number);
waiting_queue *find_plane_by_index(waiting_queue *wq, unsigned index);
void wq_del(waiting_queue *wq);
void wq_update(waiting_queue *wq, c_time local_time);
void force_land(waiting_queue *wq);

#endif
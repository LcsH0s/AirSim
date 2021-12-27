#ifndef CLASSES_H_ /* Include guard */
#define CLASSES_H_

#include "c_time.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

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

plane *p_init(float fuel_level, unsigned number, company *company, c_time *arrival);

company *c_init(char *name, char *acronym);
company **make_clist();
company **make_bl();
company *get_company_by_acronym(char *acronym);

waiting_queue *find_plane_by_number(waiting_queue *wq, unsigned number);
waiting_queue *find_plane_by_index(waiting_queue *wq, unsigned index);

void wq_add(waiting_queue *wq, plane *p);
void disp_wq(waiting_queue *wq);
void p_info(waiting_queue *wq);
void info_all(waiting_queue *wq);
void tk_init(waiting_queue *wq);
void ld_init(waiting_queue *wq);
void cmd_add(waiting_queue *wq);
void cmd_add_rand_fuel(waiting_queue *wq);
void wq_del(waiting_queue *wq);
void tk_update(waiting_queue *wq, c_time local_time, company **bl);
void ld_update(waiting_queue *wq, c_time local_time, company **bl);
void force_land(waiting_queue *wq);
void land(waiting_queue *wq);
void blacklist_add(company **bl, company *c);
void blacklist_remove(company **bl, company *c);
void disp_bl(company **bl);
void disp_clist(company **clist);
void disp_cc(company *c, waiting_queue *tk, waiting_queue *ld);

#endif
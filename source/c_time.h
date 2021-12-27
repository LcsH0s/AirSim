#ifndef C_TIME_H_ /* Include guard */
#define C_TIME_H_

typedef struct
{
    int min;
    int hour;
    int day;
    int month;
    int year;
} c_time;

void disp_time(c_time time);
void str_time(c_time time);
void update_time(c_time *l_time, unsigned old_t);
void increment_time(c_time *l_time, unsigned add);
int time_cmp(c_time a, c_time b);
void delay(unsigned int msecs);

#endif
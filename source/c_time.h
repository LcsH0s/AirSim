#ifndef C_TIME_H_ /* Include guard */
#define C_TIME_H_

struct t_time
{
    int min;
    int hour;
    int day;
    int month;
    int year;
};

void update_time(struct t_time *l_time, unsigned old_t);
void disp_time(struct t_time time);

#endif
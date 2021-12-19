#ifndef C_TIME_H_ /* Include guard */
#define C_TIME_H_

struct c_time
{
    int min;
    int hour;
    int day;
    int month;
    int year;
};

void disp_time(struct c_time time);
void update_time(struct c_time *l_time, unsigned old_t);
void increment_time(struct c_time *l_time, unsigned add);

#endif
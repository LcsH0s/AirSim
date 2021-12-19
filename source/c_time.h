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

void update_time(struct c_time *l_time, unsigned old_t);
void disp_time(struct c_time time);

#endif
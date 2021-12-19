#ifndef COMMANDS_H_ /* Include guard */
#define COMMANDS_H_

char *get_command();

int is_exit(const char *command);
int is_time_warp(const char *command);
int is_clear(const char *command);

#endif
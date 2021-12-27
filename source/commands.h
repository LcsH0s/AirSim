#ifndef COMMANDS_H_ /* Include guard */
#define COMMANDS_H_

char *get_command();

int is_exit(const char *command);
int is_time_warp(const char *command);
int is_clear(const char *command);
int is_add(const char *command);
int is_ls(const char *command);
int is_land(const char *command);
int is_del(const char *command);
int is_info(const char *command);
int is_man(const char *command);
int is_bl(const char *command);

#endif
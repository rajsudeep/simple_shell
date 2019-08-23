#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void remove_comments(char *line);
int only_delims(char *line);

/* see if program exists in path directories */
void search_path(char **args, char **env);
char *_getenv(char *name, char **env);

void replace_dollars(char **args, char **env);

/* command execution functions */
int execute(char **args);

/* string functions */
char **strtow(char *str, char *delim);
int count_words(char *str, char *delim);
int _strlen(const char *s);
char *_strstr(char *haystack, const char *needle);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
char *str_concat(char *s1, char *s2);
char *_strdup(char *str);
int _strpbrk(char *s, char accept);
void _ntoa_rev(int n, char *s);
void rev_string(char *s);

/* builtin functions and handlers */
/**
 * struct cmd_s - used to identify a built-in to execute
 * @type: an existing built-in function
 * @exec_built_in: directs to built-in function for execution
 */
typedef struct cmd_s
{
	char *type;
	int (*exec_built_in)(char **args, char **env);
} cmd_t;
int (*get_built_in(char *cmd))(char **args, char **env);
int simple_exit(char **args, char **env);
int simple_env(char **args, char **env);
int simple_history(char **args, char **env);
int simple_help(char **args, char **env);
void which_help(char *command);
int not_built_in(char **args, char **env);

#endif /* SHELL_H */

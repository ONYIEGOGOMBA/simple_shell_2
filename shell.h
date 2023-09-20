#ifndef _SHELL_H_
#define _SHELL_H_

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORMAL	0
#define CMD_ORR		1
#define CMD_ANDD	2
#define CMD_CHAINS	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define HISTO_FILE	".simple_shell_history"
#define HISTO_MAX	4096

extern char **environ;

typedef struct liststr
{
	int numb;
	char *srt;
	struct liststr *next;
} list_t;
typedef struct infopass
{
	char *arg;
	char **argv;
	list_t *env;
	int status;
	int err_numb;
	int readpd;
	list_t *alias;
	list_t *histo;
	int argc;
	char *fname;
	unsigned int line_spell;
	int linecount_lagg;
	int histocount;
	int cmd_puf_type;
	char **envir;
	list_t *envi;
	int env_change;
	char **cmd_puf;
	char *paths;
	char **environ;







}info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

struct info_t
{
	char *paths;
};

typedef struct builtin
{
	char typo;
	int (*funct)(info_t *);
} builtin_table;

/* the builtin.c */
int my_exit(info_t *);
int my_cd(info_t *);
int help_my(info_t *);

/* the atoil.c*/
int interact(info_t *);
int is_dell(char, char *);
int is_alpha(int);
int a_toil(char *);

/* the 1_builtin.c */
int my_histo(info_t *);
int my_alias(info_t *);

/* the env.c */
int my_env(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int pops_env_list(info_t *);
char *get_env(info_t *, const char *);

/* the error.c */
void _pputs(char *);
int _pputchar(char);
int _putpd(char, int);
int _putspd(char *, int);

/* the error1.c */
int _prratoi(char *);
void prints_error(info_t *, char *);
int print_f(int, int);
char *number_converter(long int, int, int);
void removes_comment(char *);

/* the exit.c */
char *_strmcat(char *, char *, int);
char *_strhr(char *, char);
char *_strmcpy(char *, char *, int);

/* the getlin.c */
ssize_t gets_input(info_t *);
int get_line(info_t *, char **, size_t *);
void signtHandler(int);

/* the get_env.c */
char **get_envir(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* the get_info.c */
void clears_info(info_t *);
void sets_info(info_t *, char **);
void frees_info(info_t *, int);

/* the memory0.c */
int cfree(void **);

/* the parsers.c */
int cmd_is(info_t *, char *);
char *chars_dup(char *, int, int);
char *finds_path(info_t *, char *, char *);

/* the strung.c */
char *start_with(const char *, const char *);
int _strlen(char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);

/* the reallocate.c */
void pfree(char **);
char *_setmem(char *, char, unsigned int);
void *_reallocate(void *, unsigned int, unsigned int);

/* the s_loop.c */
void forks_cmd(info_t *);
int finds_builtin(info_t *);
void finds_cmd(info_t *);
int ssh(info_t *, char **);

/* the list.c */
list_t *add_done(list_t **, const char *, int);
list_t *add_done_end(list_t **, const char *, int);
size_t print_lists_str(const list_t *);
int delete_node(list_t **head, unsigned int index);
void frees_lists(list_t **);

/* the list1.h */
ssize_t list_lens(const list_t *);
char **lists_to_string(list_t *);
ssize_t prints_list(const list_t *);
list_t *node_start(list_t *, char *, char);
size_t get_node(list_t *, list_t *);

/* the strung1.c */
int _putchar(char);
char *_strcpy(char *, char *);
void _puts(char *str);
char *_strdup(const char *);

/* the mercury.c */
void checks_chain(info_t *info, char *puf, size_t *a, size_t y, size_t ren);
int its_chain(info_t *info, char *puf, size_t *a);
int vars_replace(info_t *info);
int alias_replace(info_t *info);
int string_replace(char **, char *);

/* the histo.c */
char *get_histo_file(info_t *info);
int write_histo(info_t *info);
int read_histo(info_t *info);
int build_histo_list(info_t *info, char *puf, int linespell);
int renumber_histo(info_t *info);

/* the tokens.c */
char **strwot(char *, char *);
char **strwot2(char *, char);

#endif

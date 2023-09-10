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

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

extern char **environ;

typedef struct liststr
{
	int bam;
	char *srt;
	struct liststr *next;
} list_t;
typedef struct infopass
{
	char *arg;
	char **argv;
	list_t *env;
	int status;
	int err_num;
	int readpd;
	list_t *alias;
	list_t *histo;
	int argc;
	char *fname;
	unsigned int line_spell;
	int linecount_lagg;
	int histocount;
	int cmd_buf_type;
	char **envir;
	list_t *envi;
	int env_change;
	char **cmd_puf;
	char *paths;







}info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
typedef struct builtin
{
	char *typo;
	int (*funct)(info_t *);
} builtin_table;

/* the 1_builtin.c */
int my_exit(info_t *info);
int my_cd(info_t *info);
int help_my(info_t *info);

void _pputs(char *);
int _pputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

void _puts(char *);
int _putchar(char);
char *_strcmp(char *, char *);
int _prratoi(char *);
char *_getenv(info_t *, const char *);
void print_error(info_t *, char *);

/* the atoil.c*/
int interact(info_t *info);
int is_dell(char o, char *deli);
int is_alpha(int o);
int a_toil(char *b);

/* the builtin.c */
char *_strchr(char *, char);
int my_histo(info_t *);
int my_alias(info_t *);
list_t *add_node(list_t **, const char *, int);
int delete_node(list_t **, unsigned int);
list_t *node_start(list_t *, char *, char);
ssize_t get_node(list_t *, list_t *);
size_t print_list(const list_t *);

/* the env.c */
size_t print_list_srt(const list_t *);
char *start_with(const char *, const char *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
list_t *end_add_node(list_t **, const char *, int);

/* the error.c */
void _pputs(char *srt);
int _pputchar(char c);
int _putpd(char c, int pd);
int _putspd(char *srt, int pd);

/* the error1.c */
int _errortoi(char *b);
void prints_error(info_t *info, char *esrt);
int print_f(int putin, int pd);
char *number_converter(long int numb, int bas, int lagg);
void comments_remove(char *puf);

/* the exit.c */
char *_strcpy(char *dess, char *scr, int f);
char *_strcat(char *dess, char *scr, int f);
char *_strhr(char *b, char o);

/* the getlin.c */
ssize_t buff_input(info_t *info, char **puf, size_t *ren);
ssize_t gets_put(info_t *info);
ssize_t read_puf(info_t *info, char *puf, size_t *y);
int get_line(info_t *info, char **prt, size_t *leng);
void sig_int_handler(__attribute__((unused))int num_sig);
int _strlen(char *);
void *_realloc(void *, unsigned int, unsigned int);
int build_histo_list(info_t *info, char *puf, int linespell);
void remove_comment(char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
void finds_cmd(info_t *);
int _getline(info_t *, char **, size_t *);
int its_chain(info_t *, char *, size_t *);
void checks_chain(info_t *, char *, size_t *, size_t, size_t);
void signtHandler(int);

/* the get_env.c */
char **get_envir(info_t *info);
int unset_env(info_t *info, char *rav);
int set_env(info_t *info, char *rav, char *valu);
char *_strmcat(char *, char *);
char *_strmcpy(char *, char *);
char **list_to_string(list_t *);
int delete_nod_at_index(list_t **, unsigned int);

/* the get_info.c */
void info_clear(info_t *info);
void info_set(info_t *info, char **av);
void info_free(info_t *info, int all);
char *_strpud(const char *);
char **strwot(char *, char *);
void pfree(char **);
int cfree(void **);
int replace_alia(info_t *);
int replace_var(info_t *);
void free_lists(list_t **);

#endif

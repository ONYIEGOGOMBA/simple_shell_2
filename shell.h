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

extern char **environ;

typedef struct liststr
{
	int bam;
	char *str;
	struct liststr *next;
} list_t;
typedef struct infopass
{
	char *arg;
	char **argv;
	list_t *env;
	int status;
	int err_num;

}info_t;

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

#endif

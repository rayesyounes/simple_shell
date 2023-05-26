#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define USEget_line 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
#define INFO_INIT                                                         \
	{                                                                     \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, \
			NULL, 0, 0, 0                                                 \
	}

extern char **environ;

/**
 * struct liststr - linked list
 * @num: field number
 * @str: string
 * @next: pointer to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains arguments to pass into a function,
 * @arg: string generate from getline contains arguments
 * @argv: an array of string generate from arg
 * @path: string path for the current command
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit
 * @linecount_flag: count line of inputs
 * @fname: filename
 * @env: linked list for copu of env
 * @environ: custom modified copy of env
 * @history: history node
 * @alias: alias node
 * @env_changed: if env was changed
 * @status: return status of the list exec'd command
 * @cmd_buf: address point to cmd_buf
 * @cmd_buf_type: cmd_type ||,, &&, ;
 * @readfd: fd from which read line input
 * @histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

/**
 *struct builtin - contains builtin string
 *@type: builtin command flag
 *@func: function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int shell_loop(info_t *, char **);
int find_built(info_t *);

void find_command(info_t *);
void fork_command(info_t *);
int command(info_t *, char *);

char *duplicat_char(char *, int, int);
char *find_path(info_t *, char *, char *);

void putin_str(char *);
int putchar_stdr(char);
int put_fd(char, int);
int putin_sfd(char *, int);

int str_length(char *);
int str_compare(char *, char *);
char *start_with(const char *, const char *);
char *str_concat(char *, char *);

char *str_copy(char *, char *);
char *str_duplicate(const char *);
void put_str(char *);
int put_char(char);

char *strn_copy(char *, char *, int);
char *strn_concat(char *, char *, int);
char *str_locat(char *, char);

char **strto_word_1(char *, char *);
char **strto_word_2(char *, char);

char *memo_set(char *, char, unsigned int);
void free_strn(char **);
void *memo_reallocat(void *, unsigned int, unsigned int);
int free_pointer(void **);

int interact(info_t *);
int is_delim(char, char *);
int is_alphabet(int);
int ato_int(char *);

int errato_int(char *);
void put_error(info_t *, char *);
int put_decimal(int, int);
char *convert_nb(long int, int, int);
void del_comment(char *);

int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
int _myenv(info_t *);

int unset_alias(info_t *, char *);
int set_alias(info_t *, char *);
int put_alias(list_t *);

ssize_t get_input(info_t *);
int get_line(info_t *, char **, size_t *);
void signal_int_handler(int);

void clear_data(info_t *);
void set_data(info_t *, char **);
void free_data(info_t *, int);

char *get_environ(info_t *, const char *);
int set_environ(info_t *);
int unset_environ(info_t *);
int populate_environ_list(info_t *);
char **return_environ(info_t *);
int setnew_environ(info_t *, char *, char *);
int remove_environ(info_t *, char *);

char *get_history(info_t *);
int write_history(info_t *);
int read_history(info_t *);
int build_history(info_t *, char *, int);
int renumber_history(info_t *);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t put_list_str(const list_t *);
int del_node_at(list_t **, unsigned int);
void free_list(list_t **);

size_t list_length(const list_t *);
char **listto_str(list_t *);
size_t put_list(const list_t *);
list_t *nodestart_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

int chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_var(info_t *);
int replace_str(char **, char *);

#endif

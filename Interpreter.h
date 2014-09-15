/*
99: wrong input;
15: not determined
1 : '|'
2 : '<'
3 : '>'
4 : '>>'
5 : filename or arg or command
6 : built-in or arg or filename
7 : arg with star
8 : command
9 : built-in
10: input filename
11: output filename
12: arg without star

filename : 5 || 6
arg      : 5 || 6 || 7
built-in : 6
command  : 5

*/
#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>




static char *current;
static char commandline[256];
static char *commandstring[10];
static int token_type[100]={-1};
static int num_com=0;
static char * token;
static char * next;
static int num_current=0;




void checktype();
int check_commandname(char * str);
void delete_command();
void prompt();
void tokenize();
void readthisline();
void parse_command();
bool term(char *string);
bool start();
bool s1();
bool s2();
bool s3();
bool s4();



#endif /* INTERPRETER_H_ */

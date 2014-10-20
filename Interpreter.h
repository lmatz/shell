//
//  Interpreter.h
//  shell
//
//  Created by 刘智 on 14-10-12.
//  Copyright (c) 2014年 刘智. All rights reserved.
//

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
 13: empty
 filename : 5 || 6
 arg      : 5 || 6 || 7
 built-in : 6
 command  : 5
 */



#ifndef __shell__Interpreter__
#define __shell__Interpreter__

#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include "Builtin.h"

using namespace std;

//extern bool debug;
extern bool suspend;

//exeucte的东西
//extern glob_t wild_ex[3];

//
extern char *commandstring[100];
extern int num_com;
extern int token_type[100];
extern int pipe_num;
extern char * argument[3][100];
extern vector<string> symbol;
extern char *current;
extern char commandline[256];
extern char save_commandline[256];
extern char * token;
extern char * next;
extern int num_current;
extern int cd_arg;
extern bool error_exception;

extern int pipe_pos[3];
extern int arg_len[3];

void format_print();
void checktype();
int check_commandname(char * str);
void delete_command();
void prompt();
bool tokenize();
bool readthisline();
bool checkpipe();
bool checkargument();
//bool term(char *string);
bool start();
bool s1();
bool s2();
bool s3();
bool s4();
bool recursive();
bool command();
bool term();




#endif /* defined(__shell__Interpreter__) */

//
//  execute.h
//  shell
//
//  Created by 刘智 on 14-10-12.
//  Copyright (c) 2014年 刘智. All rights reserved.
//

#ifndef __shell__execute__
#define __shell__execute__

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <deque>
#include <sys/wait.h>
#include "interpreter.h"
#include "builtin.h"



extern bool debug;


extern char *commandstring[100];
extern int num_com;
extern int token_type[100];
extern int pipe_num;
extern char * argument[3][100];
extern std::vector<std::string> symbol;
extern char *current;
extern char commandline[256];
extern char * token;
extern char * next;
extern int num_current;
extern int cd_arg;
extern bool error_exception;



extern int pipe_pos[3];
extern int arg_len[3];
extern bool suspend;

void execute() ;
void dirty_work();


class job_list{
public:
    job_list();
    job_list(pid_t pid, char * s);
    ~job_list();
    job_list *next_job;
    char *job_name;
    pid_t job_pid;
};

extern job_list * first_job;





#endif /* defined(__shell__execute__) */
